define synth = dss-1
    set manufacturer = Korg
    set name = DSS-1

    define command = Program Parameter Request
        set sysex = F0 42 3n 0B 10 p F7
        set parameter = n : 0.5 : Channel
        set parameter = p : 1 : Parameter
        set alias = pr

    define command = Mode Request
        set sysex = F0 42 3n 0B 12 F7
        set parameter = n : 0.5 : Channel
        set alias = mr

    define command = PCM Data Request
        set sysex = F0 42 3n 0B 14 a b F7
        set parameter = n : 0.5 : Channel
        set parameter = a : 6 : Start Address
        set parameter = b : 6 : Last Address + 1
        set alias = pcm

    define command = Parameter Change
        set sysex = F0 42 3n 0B 41 p v F7
        set parameter = n : 0.5 : Channel
        set parameter = p : 1 :  Program
        set parameter = v : 1 : Value
        set alias = pc param parameter parameter-change

    define command = Mode Change
        set sysex = F0 42 3n 0B 42 m F7
        set parameter = n : 0.5 : Channel
        set parameter = m : 1 : Mode
        set alias = mc mode mode-change