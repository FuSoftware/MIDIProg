use std::fs::File;
use std::io::{prelude::*, BufReader};

use crate::lib::config::*;

pub struct Interpreter<'a> {
    config: Config<'a>,
    port: isize,
    channel: isize
}

impl<'a> Interpreter<'a> {
    pub fn new(c: Config<'a>) -> Interpreter<'a> {
        Interpreter {
            config: c,
            port: -1,
            channel: -1
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

    pub fn run(&mut self, command: &str) {
        let mut data = command.split(" ");
        
        match data.next().expect("Missing command") {
            "set" => match data.next().expect("Missing property to set") {
                "synth" => {
                    self.config.load_synth(data.next().expect("Missing synth id"));
                }
                "channel" => {
                    self.channel = data.next().expect("Missing channel number").parse::<isize>().expect("Failed to parse channel number");
                }
                _ => println!("Unknown property")
            }

            "midi" => (),

            "sysex" => {
                let alias = data.next().expect("Missing command alias");
                if self.config.aliases.contains_key(alias) {
                    let mut p: Vec<usize> = Vec::new();
                    while let Some(arg) = data.next() {
                        p.push(arg.parse::<usize>().expect("Could not parse argument value"));
                    }
                    self.midi(alias, p);
                } else {
                    println!("Alias not found");
                }
            }

            _ => ()
        }
    }

    pub fn midi(&self, command: &str, a: Vec<usize>) {
        let mut args = a;
        if self.channel > -1 {args.insert(0, self.channel as usize)}
        let c: String = self.config.aliases.get(command).expect("Command not found").build_vec(args);
        println!("{}", c);
    }
}