synth
    -id "dw-8000"
    -manufacturer "Korg"
    -name "DW-8000"

command
    -name "Parameter change"
    -midi "F0 42 3n 03 41 p v F7"
    -@parameter "n : 0.5 : Channel"
    -@parameter "p : 1 : Parameter"
    -@parameter "v : 1 : Value"
    -alias "pc param parameter parameter-change"

command
    -name "Device ID Request"
    -midi "F0 42 4n F7"
    -@parameter "n : 0.5 : Channel"
    -alias "id device-id-request"

command
    -name "Write Request"
    -midi "F0 42 3n 03 11 p F7"
    -@parameter "n : 0.5 : Channel"
    -@parameter "p : 1 : Program"
    -alias "write-request"

command
    -name "Data Save Request"
    -midi "F0 42 3n 03 10 F7"
    -@parameter "n : 0.5 : Channel"
    -alias "data-save-request"