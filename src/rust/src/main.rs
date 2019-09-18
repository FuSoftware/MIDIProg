mod lib;

#[macro_use] extern crate lazy_static;

use std::time::{Duration, Instant};
use lib::utils::command_parser::*;
use lib::config::Config;
use lib::data::synth::Synth;
use lib::data::midi_command::MIDICommand;

fn test_command_parsing_n(n: u128) {
    let mut m: u128 = 0;

    for x in 0..n {
        m += test_command_parsing();
    }
    println!("Ran {} iterations in {} ms ({}us/it)", n, m / 1000, m / n)
}

fn test_command_parsing() -> u128 {
    let now = Instant::now();
    let v = parse_commands_file("/home/fuguet/Prog/MIDIProg/data/dss-1.cmd");
    let us = now.elapsed().as_micros();

    
    for c in v {
        println!("{}", c.name);
        for p in c.parameters.keys() {
            println!("    {} : {}", p, c.get_parameter_from_key(p));
        }
    }
    us
}

fn test_config_n(n: u128) {
    let mut m: u128 = 0;

    for x in 0..n {
        m += test_config();
    }
    println!("Ran {} iterations in {} ms ({}us/it)", n, m / 1000, m / n)
}

fn test_config() -> u128 {
    let now = Instant::now();
    let mut c = Config::new();
    c.run_file("/home/fuguet/Prog/MIDIProg/data/config.cmd");
    let us = now.elapsed().as_micros();
    
    for s in c.synths {
        let synth = s.1;
        println!("({}) {} {}", synth.id, synth.manufacturer, synth.name);
        for comm in synth.commands {
            println!("   {} => {}", comm.name, comm.midi);
        }
    }

    us
}

fn main() {
    test_config_n(500);
}
