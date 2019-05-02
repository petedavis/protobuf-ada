
#include <string>
#include <fstream>
#include <iostream>
#include <google/protobuf/compiler/plugin.h>
#include <google/protobuf/compiler/command_line_interface.h>
#include <ada_generator.h>
using namespace std;

static void _Trace(char *s){
  ofstream outfile;
  outfile.open(s);
  outfile << "Trace " <<s << endl;
  outfile.close();

}


int main(int argc, char* argv[]) {
  google::protobuf::compiler::CommandLineInterface cli;

  std::string invocation_name = argv[0];
  std::string invocation_basename = invocation_name.substr(invocation_name.find_last_of("/") + 1);
  const std::string legacy_name = "protoc-gen-ada";

  google::protobuf::compiler::ada::AdaGenerator ada_generator;

  ofstream outfile;
  outfile.open("Trace.txt");
  for(int i=0; i<argc; i++) {
    outfile << invocation_basename << endl;
    outfile <<  legacy_name << endl;
    if (invocation_basename == legacy_name) {
      outfile <<  "<<<<<<<<<<<<<<<<<<<<<<" << endl;
    }else{
        outfile <<  ">>>>>>>>>>>>>>>>>>>" << endl;
    };
  }
  outfile.close();

//  if (invocation_basename == legacy_name) {
//     _Trace("5.txt");
//    cli.RegisterGenerator("--ada_out", &ada_generator, "Generate Ada specification and body.");
//    _Trace("6.txt");
//    return cli.Run(argc, argv);
    //  _tracer("7.txt");
//  };
  _Trace("8.txt");
  return google::protobuf::compiler::PluginMain(argc, argv, &ada_generator);
}
