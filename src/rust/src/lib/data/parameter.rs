#[derive(Clone)]
pub struct Parameter {
    size: f32,
    name: String,
}

impl Parameter {
    pub fn new(name: String, size: f32) -> Parameter {
        Parameter {
            size,
            name,
        }
    }

    pub fn get_value(&self, val: usize) -> String {
        format!("{:01$X}", val, self.characters())    
    }

    pub fn characters(&self) -> usize {
        (self.size * 2.0).round() as usize
    }
}
