mod lib;

use std::time::{Duration, Instant};
use lib::interpreter::*;
use lib::config::*;

fn main() {
    let now = Instant::now();
    let c: Config = Config::new_from_file("data/config.cmd");
    c.print_synth_keys();

    //let mut i: Interpreter = Interpreter::new(c);
    //i.run_file("data/commands.cmd");
    //println!("{}us", now.elapsed().as_micros());
}