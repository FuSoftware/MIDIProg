use crate::lib::data::midi_command::MIDICommand;
use crate::lib::data::parameter::Parameter;
use crate::lib::data::synth::Synth;
use std::collections::HashMap;
use std::fs::File;
use std::io::{prelude::*, BufReader};

use std::rc::Rc;

pub struct Config {
    pub synths: HashMap<String, Synth>,
    pub aliases: HashMap<String, MIDICommand>,
    pub curr_synth: &Synth,
}

impl Config {
    pub fn new() -> Config {
        Config {
            synths: HashMap::new(),
            aliases: HashMap::new(),
            curr_synth: None,
        }
    }

    pub fn new_from_file(path: &str) -> Config {
        let mut c = Config::new();
        c.run_file(path);
        c
    }

    pub fn print_synth_keys(&self) {
        println!("{}", self.synths.keys().len());
        for k in self.synths.keys() {
            println!("{}", k)
        }
    }

    pub fn load_synth(&mut self, id: &str) {
        println!("Loading synth {}", id);
        let sid = id.to_owned();
        if self.synths.contains_key(&sid) {
            println!("Synth found");
            let synth = &self.synths[&sid];
            self.aliases.clear();
            for c in &synth.commands {
                for a in &c.alias {
                    println!("Loading alias {}", a);
                    self.aliases.insert(String::from(a), c.clone());
                }
            }
        } else {
            println!("Synth not found");
        }
    }

    pub fn run_file(&mut self, path: &str) {
        let file: File = File::open(path).unwrap();
        let reader = BufReader::new(file);

        for line in reader.lines() {
            let l = line.as_ref().unwrap().trim();
            if l != "" {
                self.run(l);
            }
        }
    }

    pub fn save_synth(&mut self) {
        let s = self.curr_synth.take().expect("Trying to save a synth but none was being created");
        println!("Saving synth {}", s.id);
        self.synths.insert(s.id.clone(), s);
    }

    pub fn current_synth(&mut self) -> &mut Synth {
        self.curr_synth.as_mut().expect("Trying to load a synth but none was created")
    }

    pub fn current_command(&mut self) -> &mut MIDICommand {
        self.current_synth().commands.last_mut().unwrap()
    }

    pub fn run(&mut self, line: &str) {
        let mut split = line.split("=");
        let command: &str = split.next().expect("Missing command").trim();

        match command {
            "source" => {
                let file = split.next().expect("Missing file name").trim();
                println!("Parsing file {}", &file);
                self.run_file(file);
            }
            "define synth" => {
                let synth_name = split.next().expect("Missing synth name").trim();
                println!("Defining synth {}", &synth_name);
                let s: Synth = Synth::new(String::from(synth_name));
                self.curr_synth = Some(s);
            }
            "define command" => {
                self.save_synth();
                let command_name = split.next().expect("Missing command name").trim();
                println!("Defining command {}", &command_name);
                let c: MIDICommand = MIDICommand::new(String::from(command_name));
                self.current_synth().commands.push(c);
            }
            "set manufacturer" => {
                let name = split.next().expect("Missing manufacturer").trim();
                self.current_synth().manufacturer = String::from(name);
            }
            "set name" => {
                let name = split.next().expect("Missing name").trim();
                self.current_synth().name = String::from(name);
            }
            "set sysex" => {
                let midi = split.next().expect("Missing MIDI data").trim();
                self.current_command().midi = String::from(midi);
            }
            "set parameter" => {
                let mut params = split.next().expect("Missing parameter data").split(":");
                let k = params.next().expect("Missing parameter id").trim();
                let d = params.next().expect("Missing parameter size").trim().parse::<f32>().expect("Couldn't parse parameter size");
                let v = params.next().expect("Missing parameter name").trim();
                let p: Parameter = Parameter::new(String::from(v), d);
                self.current_command().parameters.insert(String::from(k), p);
            }
            "set alias" => {
                let aliases: Vec<&str> = split.next().expect("Missing Alias data").split(" ").collect();
                for a in aliases {
                    self.current_command().alias.push(String::from(a.trim()));
                }
            }
            _ => (),
        }
    }
}
