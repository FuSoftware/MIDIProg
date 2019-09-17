extern crate regex;
use std::fs::File;
use std::io::prelude::*;

use std::collections::HashMap;
use regex::Regex;

pub struct Command {
    pub name: String,
    pub parameters: HashMap<String, String>,
    pub values: Vec<String>
}

impl Command {
    pub fn new() -> Command {
        Command {
            name: String::from(""),
            parameters: HashMap::new(),
            values: Vec::new()
        }
    }

    pub fn add_parameter(&mut self, k: String, v: String){
        self.values.push(v.clone());
        self.parameters.insert(k, v);
    }

    pub fn get_parameter_from_key(&self, key: &str) -> &String {
        self.parameters.get(key).expect("Key not found")
    }

    pub fn get_parameter_from_index(&self, index: usize) -> &String {
        self.values.get(index).expect("Index out of bounds")
    }

    pub fn has_parameter(&self, key: &str) -> bool {
        self.parameters.contains_key(key)
    }

    pub fn has_numbered_parameter(&self, p: &str, index: usize) -> bool {
        let mut key = String::from(p);
        key.push('_');
        key.push_str(index.to_string().as_str());
        self.parameters.contains_key(&key)
    }

    pub fn get_numbered_parameter(&self, p: &str, index: usize) -> &String {
        let mut key = String::from(p);
        key.push('_');
        key.push_str(index.to_string().as_str());
        self.get_parameter_from_key(&key)
    }
}

pub fn get_commands_file(path: &str) -> Vec<String> {
    let mut file = File::open(path).expect("Could not open file");
    let mut contents = String::new();
    file.read_to_string(&mut contents).expect("Could not read file");
    get_commands(&contents)
}

pub fn get_commands(data: &String) -> Vec<String> {
    let mut current_command: String = String::from("");
    let mut commands: Vec<String> = Vec::new();
    
    let lines = data.split('\n');

    for line in lines {
        let l: String = String::from(line.trim());
        
        if l != "" {
            if l.starts_with('-') {
                current_command += line;
            } else if current_command == "" {
                current_command = l;
            } else {
                commands.push(current_command);
                current_command = l;
            }
        }
    }

    if current_command != "" {
        commands.push(current_command);
    }

    commands
}

pub fn parse_commands_file(path: &str) -> Vec<Command> {
    parse_commands(get_commands_file(path))
}

pub fn parse_commands(data: Vec<String>) -> Vec<Command> {
    let mut commands: Vec<Command> = Vec::new();

    for c in data {
        commands.push(parse_command(&c));
    }

    commands
}

pub fn parse_command(data: &String) -> Command {
    let mut command: Command = Command::new();

    lazy_static! {
        static ref r_params: Regex = Regex::new("-(\\S+) \"([^\"]+)\"").unwrap();
        static ref r_comm: Regex = Regex::new("([^\"\\s]+)(\\s?+)-").unwrap();
    }

    let mut count: HashMap<String, usize> = HashMap::new();

    if r_comm.is_match(data) {
        let caps = r_comm.captures(data).expect("No captures found");
        command.name = String::from(caps.get(1).expect("Capture group not found for the command name").as_str());
    }

    for caps in r_params.captures_iter(data) {
        let mut p = String::from(caps.get(1).expect("Capture group not found for the command name").as_str());
        if p.starts_with("@") {
            if !count.contains_key(&p) {
                count.insert(p.clone(), 0);
            }
            let c: usize = count[&p.clone()];
            *count.get_mut(&p.clone()).expect("...") += 1;
            p.remove(0);
            p.push('_');
            p.push_str(c.to_string().as_str());
        }

        command.add_parameter(p, String::from(caps.get(2).expect("Capture group not found for the command name").as_str()));
    }

    command
}
