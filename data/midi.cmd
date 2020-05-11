synth
    -id "midi"
    -manufacturer "Generic"
    -name "MIDI Standard"

command
    -name "Note Off"
    -midi "8n k v"
    -@parameter "n : 0.5 : Channel"
    -@parameter "k : 1 : Key"
    -@parameter "v : 1 : Velocity"
    -alias "note-off note- noteoff noff n-"

command
    -name "Note On"
    -midi "9n k v"
    -@parameter "n : 0.5 : Channel"
    -@parameter "k : 1 : Key"
    -@parameter "v : 1 : Velocity"
    -alias "note-on note+ noteon non n+"

command
    -name "Polyphonic Key Pressure"
    -midi "An k v"
    -@parameter "n : 0.5 : Channel"
    -@parameter "k : 1 : Key"
    -@parameter "v : 1 : Velocity"
    -alias "polyphonic-key-pressure polykey poly pk"

command
    -name "Control Change"
    -midi "Bn c v"
    -@parameter "n : 0.5 : Channel"
    -@parameter "c : 1 : Controller"
    -@parameter "v : 1 : Value"
    -alias "control-change control cc"

command
    -name "Program Change"
    -midi "Cn p"
    -@parameter "n : 0.5 : Channel"
    -@parameter "p : 1 : Program"
    -alias "program-change program pc"

command
    -name "Channel Pressure"
    -midi "Dn v"
    -@parameter "n : 0.5 : Channel"
    -@parameter "v : 1 : Pressure"
    -alias "channel-pressure cp"

command
    -name "Pitch Bend Change"
    -midi "En l m"
    -@parameter "n : 0.5 : Channel"
    -@parameter "l : 1 : LSB"
    -@parameter "m : 1 : MSB"
    -alias "pitch-bend-change pitch pitch-bend pb"

