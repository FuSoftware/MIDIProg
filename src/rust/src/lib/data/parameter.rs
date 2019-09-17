#[derive(Clone)]
pub struct Parameter {
    pub key: String,
    pub name: String,
    pub size: f32,
}

impl Parameter {
    pub fn new(key: String, name: String, size: f32) -> Parameter {
        Parameter {
            key,
            size,
            name,
        }
    }

    pub fn new_from_str(data: &str) -> Parameter {
        let tokens : Vec<String> = data.split(' ').map(|v| String::from(v.trim())).collect();
        let key: String = tokens.get(0).expect("Parameter name not found").clone();
        let size: f32 = tokens.get(1).expect("Parameter name not found").parse::<f32>().expect("Conversion failed");
        let name: String = tokens.get(2).expect("Parameter name not found").clone();
        Parameter::new(key, name, size)
    }

    pub fn midi(&self, val: usize) -> String {
        format!("{:01$X}", val, self.characters())    
    }

    pub fn characters(&self) -> usize {
        (self.size * 2.0).round() as usize
    }
}
