extern crate midir;
use midir::MidiInput;
use midir::MidiOutput;

pub fn list_ports() {
    list_inputs();
    list_outputs();
}

fn list_inputs() {
    let mid: MidiInput = MidiInput::new("test").unwrap();

    let ports = mid.port_count();

    println!("MIDI Inputs : ");
    for x in 0..ports {
        println!("Port {} : {}", x, mid.port_name(x).unwrap());
    }
    println!("");
}

fn list_outputs() {
    let mid: MidiOutput = MidiOutput::new("test").unwrap();

    let ports = mid.port_count();

    println!("MIDI Outputs : ");
    for x in 0..ports {
        println!("Port {} : {}", x, mid.port_name(x).unwrap());
    }
    println!("");
}