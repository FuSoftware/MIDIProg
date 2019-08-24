use crate::lib::data::midi_command::MIDICommand;

#[derive(Clone)]
pub struct Synth {
    pub name: String,
    pub id: String,
    pub manufacturer: String,
    pub commands: Vec<MIDICommand>,
}

impl Synth {
    pub fn new(id: String) -> Self {
        Self {
            name: String::new(),
            id: id,
            manufacturer: String::new(),
            commands: Vec::new(),
        }
    }
}
