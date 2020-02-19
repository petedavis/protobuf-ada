# Ada implementation of Protocol Buffers - Google's data interchange format

Note this repository is in beta stage.

## Prereqisits the folowing packages installed:
* protobuf-compiler and protobuf-devel version 3.7.1
* Or the protobuff (version 3.7.1) packages installed in the GNAT-Installation.
* the file ```libstdcpp.gpr``` in ```${GNATHOME}/lib/gnat``` 
**  The intent of this file is to provide an ```RPATH``` to the final executable.
**  Ther is a sample of this file in the ```prerqisits/``` folder.
## How to build and install.

```
$make all
$make install prefix=${PREFIX} # defaults to the gprinstall default.
```
