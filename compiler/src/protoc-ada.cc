#include <string>
#include <fstream>
#include <iostream>
#include <google/protobuf/compiler/plugin.h>
#include <google/protobuf/compiler/command_line_interface.h>
#include <ada_generator.h>
#include <port_def.inc>
using namespace std;


int main(int argc, char* argv[]) {
  google::protobuf::compiler::CommandLineInterface cli;

  std::string invocation_name = argv[0];
  std::string invocation_basename = invocation_name.substr(invocation_name.find_last_of("/") + 1);

  const std::string legacy_name = "protoc-gen-ada";




  google::protobuf::compiler::ada::AdaGenerator *ada_generator = new google::protobuf::compiler::ada::AdaGenerator();

  if (invocation_basename == legacy_name) {
    cli.RegisterGenerator("--ada_out", ada_generator, "Generate Ada specification and body.");

    return cli.Run(argc, argv);
  } else {
    return google::protobuf::compiler::PluginMain(argc, argv, ada_generator);
  };
}
