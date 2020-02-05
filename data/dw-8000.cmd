synth
    -id "dw-8000"
    -manufacturer "Korg"
    -name "DW-8000"

command
    -name "Parameter change"
    -midi "F0 42 3n 03 41 p v F7"
    -@parameter "n : 0.5 : Channel"
    -@parameter "p : 1 : Program"
    -@parameter "v : 1 : Value"
    -alias "pc param parameter parameter-change"