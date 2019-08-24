extern crate midir;
extern crate hex;
use midir::MidiOutputConnection;

pub fn send_message(conn: &mut MidiOutputConnection, message: Vec<u8>) {
    conn.send(&message);
}

pub fn str_to_u8(message: &str) -> Vec<u8> {
    let mut mess : String = String::from(message);
    if mess.contains(" ") {
        mess = mess.replace(" ", "");
    }
    hex::decode(mess).expect("Decoding HEX failed")
}