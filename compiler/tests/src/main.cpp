#include <string>
#include <fstream>
#include <iostream>
#include <google/protobuf/compiler/plugin.h>
#include <google/protobuf/compiler/command_line_interface.h>
#include <ada_generator.h>
#include <port_def.inc>
using namespace std;

#define REQIRED_PROTOBUF_VERSION 3007001

int main() {

  google::protobuf::compiler::CommandLineInterface cli;

  char *argv[] = {(char*)"main",(char*)"--ada_out",(char*)"out",(char*)"test.proto"};
  int  argc = 4;
  google::protobuf::compiler::ada::AdaGenerator *ada_generator = new google::protobuf::compiler::ada::AdaGenerator();

  cli.RegisterGenerator("--ada_out", ada_generator, "Generate Ada specification and body.");
  return cli.Run(argc, argv);
}
