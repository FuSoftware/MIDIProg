import 'dart:io';

class Synth {
  String name;
  String id;
  String manufacturer;
  List<MIDICommand> commands = [];

  Synth({this.id});
}

class Parameter {
  double size;
  String name;

  int characters() => (this.size * 2.0).round();

  Parameter(this.name, this.size);

  String getFormattedValue(int val) {
    String v = this.getValue(val);
    return v.splitMapJoin(
      RegExp(r'(..)'),
      onMatch: (m) => ' ${m.group(0)}',
      onNonMatch: (n) => n
    ).trim();
  }

  String getValue(int val) => val.toRadixString(16).padLeft(this.characters(), "0");
}

class MIDICommand {
  String name;
  String midi;
  Map<String, Parameter> parameters = {};
  List<String> aliases = [];

  MIDICommand({this.name});
  String toString() => "$name"; 

  String generate(List<int> values) {
    if (values.length != this.parameters.length) {
      return "";
    } else {
      Map<String, String> val = {};
      List<String> keys = this.parameters.keys.toList();
      for(int i=0;i<values.length;i++) {
        val[keys[i]] = this.parameters[keys[i]].getFormattedValue(values[i]);
      }
      return this.generateArgs(val);
    }
  }

  String generateArgs(Map<String, String> values) {
    String midi = this.midi;

    values.keys.forEach((k){
      midi = midi.replaceAll(k, values[k]);
    });

    return midi.toUpperCase();
  }

}

class Config {
  List<Synth> temp_synth = [];
  Map<String, Synth> synths = {};
  Map<String, MIDICommand> aliases = {};
  MIDICommand currCommand;
  Synth currSynth;
  String currentItem = "";

  loadAliases(Synth synth) {
    this.aliases.clear();
    synth.commands.forEach((c){
      c.aliases.forEach((a){
        this.aliases[a] = c;
      });
    });
  }

  loadSynths() {
    this.temp_synth.forEach((s) {
      this.synths[s.id] = s;
    });
  }

  runConfigFile(String path) {
    Stopwatch stopwatch = new Stopwatch()..start();
    new File(path).readAsLinesSync().forEach((line) {
      if(line.trim() != "") this.runConfigLine(line);
    });
    print("Ran in ${stopwatch.elapsedMilliseconds}ms");
  }

  runConfigLine(String line) {
    List<String> data = line.split("=");
    data = data.map((s) => s.trim()).toList();

    //print("Parsing command '${data[0]}' with data '${data[1]}'");

    switch(data[0]) {
      case "source" :
        print("Parsing file ${data[1]}");
        this.runConfigFile(data[1]);
        break;

      case "define synth":
        this.currSynth = Synth(id: data[1]);
        this.temp_synth.add(currSynth);
        this.currentItem = "synth";
        print("Defining synth ${this.currSynth.name}");
        break;

      case "define command":
        this.currCommand = MIDICommand(name: data[1]);
        this.currSynth.commands.add(currCommand);
        this.currentItem = "command";
        print("Defining command ${this.currCommand.name} for synth ${this.currSynth.name}");
        break;

      case "set manufacturer":
        this.currSynth.manufacturer = data[1];
        print("Setting manufacturer ${data[1]}");
        break;

      case "set name":
        this.currSynth.name = data[1];
        print("Setting synth name ${data[1]}");
        break;

      case "set sysex":
        this.currCommand.midi = data[1];
        print("Setting sysex ${data[1]}");
        break;

      case "set parameter":
        List<String> p = data[1].split(":").map((s)=>s.trim()).toList();
        this.currCommand.parameters[p[0]] = Parameter(p[2], double.parse(p[1]));
        print("Setting parameter ${p[0]} = ${p[2]} (${p[1]} bytes)");
        break;

      case "set alias":
        List<String> p = data[1].split(" ");
        this.currCommand.aliases = p;
        print("Setting aliases ${p}");
        break;

      default:
        break;
    }
  }

  loadSynth(String id) {
    if(this.synths.keys.contains(id)) {
      this.loadAliases(this.synths[id]);
    } else {
      print("Synth $id not found");
    }
  }
}

class Interpreter {
  Config config;
  int channel = -1;

  Interpreter(this.config);

  runFile(String path){
    File(path).readAsLinesSync().forEach((l){
      if(l.trim() != "") this.run(l);
    });
  }

  run(String command) {
    List<String> data = command.split(" ").map((s) => s.trim()).toList();

    switch(data[0]) {
      case "set":
        switch(data[1]) {
          case "synth":
            this.config.loadSynth(data[2]);
            break;

          case "channel":
            this.channel = int.parse(data[2]);
            break;
        }
        break;

      case "midi" :
        break;

      case "sysex":
        String c = data[1];
        if(this.config.aliases.containsKey(c)) {
          List<int> p = [];
          for(int i=2; i<data.length;i++) {
            p.add(int.parse(data[i]));
          }
          this.sysex(c, p);
        }else {
          print("Command not found");
        }
        break;
      default:
        print("Unhandled command : ${data[0]}");
        break;
    }
  }

  sysex(String command, List<int> arguments) {
    if(channel > -1) arguments.insert(0, this.channel);
    String c =  this.config.aliases[command].generate(arguments);
    print(c);
  }
}

main() {
  Stopwatch sw = Stopwatch()..start();
  Config c = Config();
  c.runConfigFile('config.cmd');
  c.loadSynths();
  print(c.synths);

  Interpreter i = Interpreter(c);
  i.runFile("commands.cmd");
  print("Program ran in ${sw.elapsedMilliseconds}ms");
}