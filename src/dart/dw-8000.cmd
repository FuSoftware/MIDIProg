define synth = dw-8000
    set manufacturer = Korg
    set name = DW-8000

    define command = Parameter Change
        set sysex = F0 42 3n 03 41 p v F7
        set parameter = n : 0.5 : Channel
        set parameter = p : 1 :  Program
        set parameter = v : 1 : Value
        set alias = pc param parameter parameter-change
