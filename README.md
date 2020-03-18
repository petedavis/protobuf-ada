# Ada implementation of Protocol Buffers - Google's data interchange format

Note this repository is in beta stage.

## Prereqisits the folowing packages installed:
* protobuf-compiler and protobuf-devel version >3.0.0 protobuf-compiler proviode libprotoc.so and libproto.so, these libraries are requred by the protoc-ada compiler but not in runtime.
* the file ```libstdcpp.gpr``` in ```${GNATHOME}/lib/gnat``` 
**  The intent of this file is to provide an ```RPATH``` to the final executable.
**  Ther is a sample of this file in the ```prerqisits/``` folder.
## How to build and install.
```
$make setup
$make compile
$make test
$make install PREFIX=${what ever}  (defaults to the gprbuild:s home)
```
# Cavetas when target language is Ada.
* It is not possible to reopen a namespace since the namespace is mapped agains Ada:s package, so when a namespace is closed it is final.
* Identifiers are not case-sensetive as in C,C++,Java,
