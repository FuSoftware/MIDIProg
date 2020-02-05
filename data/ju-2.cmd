synth
    -id "ju-2"
    -manufacturer "Roland"
    -name "Alpha Juno 2"

command
    -name "Individual Tone Parameter"
    -midi "F0 41 36 0n 20 01 p v F7"
    -@parameter "n : 0.5 : Channel"
    -@parameter "p : 1 : Parameter"
    -@parameter "v : 1 : Value"
    -alias "ipr parameter param"

command
    -name "Want Send File"
    -midi "F0 41 40 0n 23 F7"
    -@parameter "n : 0.5 : Channel"
    -alias "wsf sendfile"

command
    -name "Request File"
    -midi "F0 41 41 0n 23 F7"
    -@parameter "n : 0.5 : Channel"
    -alias "rqf requestfile"

command
    -name "Acknowledge"
    -midi "F0 41 43 0n 23 F7"
    -@parameter "n : 0.5 : Channel"
    -alias "ack"