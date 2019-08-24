use std::collections::BTreeMap;
use crate::lib::data::parameter::Parameter;

#[derive(Clone)]
pub struct MIDICommand {
    pub name: String,
    pub midi: String,
    pub parameters: BTreeMap<String, Parameter>,
    pub alias: Vec<String>
}

impl MIDICommand {
    pub fn new(name: String) -> MIDICommand {
        MIDICommand {
            name: name,
            midi: String::new(),
            parameters: BTreeMap::new(),
            alias: Vec::new(),
        }
    }

    pub fn build_hash(&self, params: BTreeMap<String, String>) -> String {
        let mut c : String = self.midi.clone();
        for k in params.keys() {
            let h: String = params[k].clone();
            c = c.replace(k, h.as_str());
        }
        return c;
    }

    pub fn build_vec(&self, params: Vec<usize>) -> String {
        let mut p: BTreeMap<String, String> = BTreeMap::new();
        let mut i: usize = 0;

        for k in self.parameters.keys() {
            let v: String = self.parameters[k].get_value(params[i]);
            p.insert(k.to_owned(), v);
            i = i+1;
        }

        return self.build_hash(p);
    }
}
