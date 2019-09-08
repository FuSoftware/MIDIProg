synth
    -id "dss-1"
    -manufacturer "Korg"
    -name "DSS-1"

command
    -name "Program Parameter Request"
    -sysex "F0 42 3n 0B 10 p F7"
    -@parameter "n : 0.5 : Channel"
    -@parameter "p : 1 : Parameter"
    -alias "pr"

command
    -name "Mode Request"
    -sysex "F0 42 3n 0B 12 F7"
    -@parameter "n : 0.5 : Channel"
    -alias "mr"

command 
    -name "PCM Data Request"
    -sysex "F0 42 3n 0B 14 a b F7"
    -@parameter "n : 0.5 : Channel"
    -@parameter "a : 6 : Start Address"
    -@parameter "b : 6 : Last Address + 1"
    -alias "pcm"

command
    -name "Parameter Change"
    -sysex "F0 42 3n 0B 41 p v F7"
    -@parameter "n : 0.5 : Channel"
    -@parameter "p : 1 : Parameter"
    -@parameter "v : 1 : Value"
    -alias "pc param parameter parameter-change"

command
    -name "Mode Change"
    -sysex "F0 42 3n 0B 42 m F7"
    -@parameter "n : 0.5 : Channel"
    -@parameter "m : 1 : Mode"
    -alias "mc mode mode-change"