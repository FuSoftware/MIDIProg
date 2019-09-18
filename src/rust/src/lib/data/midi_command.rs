use std::collections::BTreeMap;
use crate::lib::data::parameter::Parameter;
use crate::lib::utils::midi::*;

#[derive(Clone)]
pub struct MIDICommand {
    pub name: String,
    pub midi: String,
    pub parameters: BTreeMap<String, Parameter>,
    pub alias: Vec<String>,
    pub param_names: Vec<String>,
}

impl MIDICommand {
    pub fn new(name: String) -> MIDICommand {
        MIDICommand {
            name: name,
            midi: String::new(),
            parameters: BTreeMap::new(),
            alias: Vec::new(),
            param_names: Vec::new()
        }
    }

    pub fn generate_hash(&self, params: BTreeMap<String, String>) -> String {
        let mut c : String = self.midi.clone();
        for k in params.keys() {
            let h: String = params[k].clone();
            c = c.replace(k, h.as_str());
        }
        return c;
    }

    pub fn generate_vec(&self, params: Vec<usize>) -> String {
        let mut p: BTreeMap<String, String> = BTreeMap::new();
        let mut i: usize = 0;

        for k in self.parameters.keys() {
            let v: String = self.parameters[k].midi(params[i]);
            p.insert(k.to_owned(), v);
            i = i+1;
        }

        return self.generate_hash(p);
    }

    pub fn generate_bytes_hash(&self, params: BTreeMap<String, String>) -> Vec<u8> {
        str_to_u8(self.generate_hash(params).as_str())
    }

    pub fn generate_bytes_vec(&self, params: Vec<usize>) -> Vec<u8> {
        str_to_u8(self.generate_vec(params).as_str())
    }

    pub fn add_parameter(&mut self, p: Parameter) {
        let s = p.key.clone();
        self.parameters.insert(s.clone(), p);
        self.param_names.push(s);
    }

    pub fn add_aliases_str(&mut self, a: String) {
        let v = a.split(' ').map(|s| String::from(s.trim())).collect();
        self.add_aliases(v);
    }

    pub fn add_aliases(&mut self, a: Vec<String>) {
        for v in a {
            self.alias.push(v.clone());
        }
    }
}
