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
    -alias "noteoff noff n-"

command
    -name "Note On"
    -midi "9n k v"
    -@parameter "n : 0.5 : Channel"
    -@parameter "k : 1 : Key"
    -@parameter "v : 1 : Velocity"
    -alias "noteon non n+"

command
    -name "Polyphonic Key Pressure"
    -midi "An k v"
    -@parameter "n : 0.5 : Channel"
    -@parameter "k : 1 : Key"
    -@parameter "v : 1 : Velocity"
    -alias "polykey poly pk"

command
    -name "Control Change"
    -midi "Bn c v"
    -@parameter "n : 0.5 : Channel"
    -@parameter "c : 1 : Controller"
    -@parameter "v : 1 : Value"
    -alias "controlchange control cc"

command
    -name "Program Change"
    -midi "Cn p"
    -@parameter "n : 0.5 : Channel"
    -@parameter "p : 1 : Program"
    -alias "program pc"

command
    -name "Channel Pressure"
    -midi "Dn v"
    -@parameter "n : 0.5 : Channel"
    -@parameter "v : 1 : Pressure"
    -alias "channelpressure cp"

command
    -name "Pitch Bend Change"
    -midi "En l m"
    -@parameter "n : 0.5 : Channel"
    -@parameter "l : 1 : LSB"
    -@parameter "m : 1 : MSB"
    -alias "pitch pitchbend pb"

