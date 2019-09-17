use crate::lib::data::midi_command::MIDICommand;
use crate::lib::data::parameter::Parameter;
use crate::lib::data::synth::Synth;
use crate::lib::utils::command_parser::*;

use std::collections::HashMap;


pub struct Config {
    pub synths: HashMap<String, Synth>,
    pub aliases: HashMap<String, MIDICommand>,
    pub curr_synth: String,
}

impl Config {
    pub fn new() -> Config {
        Config {
            synths: HashMap::new(),
            aliases: HashMap::new(),
            curr_synth: String::new(),
        }
    }

    pub fn get_synth(&mut self, id: &str) -> &mut Synth {
        self.synths.get_mut(id).expect("Synth not found")
    }

    pub fn get_current_synth(&self) -> &mut Synth {
        let key = self.curr_synth.as_str();
        self.get_synth(key)
    }

    pub fn run_file(&mut self, path: &str) {
        let commands = parse_commands_file(path);
        self.run_commands(commands);
    }

    pub fn run_commands(&mut self, commands: Vec<Command>) {
        for c in commands {
            self.run_command(c);
        }
    }

    pub fn run_command(&mut self, c: Command) {
        match c.name.as_str() {
            "synth" => {
                let id = c.get_parameter_from_key("id").clone();
                let mut synth: Synth = Synth::new(id);
                if c.has_parameter("name") {synth.name = c.get_parameter_from_key("name").clone()}
                if c.has_parameter("manufacturer") {synth.manufacturer = c.get_parameter_from_key("manufacturer").clone()}
                self.curr_synth = synth.id.clone();
                self.synths.insert(synth.id.clone(), synth);
            },
            "command" => {
                if self.curr_synth != "" {
                    let mut comm: MIDICommand = MIDICommand::new(c.get_parameter_from_key("name").clone());
                    comm.add_aliases_str(c.get_parameter_from_key("alias").clone());
                    comm.midi = c.get_parameter_from_key("sysex").clone();

                    let mut i: usize = 0;
                    let key = "parameter";

                    while c.has_numbered_parameter(key, i) {
                        let p: String = c.get_numbered_parameter(key, i).clone();
                        i += 1;
                        comm.add_parameter(Parameter::new_from_str(p.as_str()));
                    }

                    self.get_current_synth().commands.push(comm);
                }
            },
            "source" => {

            },
            "folder" => {

            }
            _ => {
                println!("Unrecognized command : {}", c.name);
            }
        }
    }
}
