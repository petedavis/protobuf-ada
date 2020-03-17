# Protobuf for Ada

# Prereqisits
protobuf-compipler installed to proviode libprotoc.so and libproto.so, these libraries are requred by the protoc-ada compiler but not in runtime.

# How to install
'''$make setup
$make compile
$make test
$make install PREFIX=${what ever}  (defaults to the gprbuild:s home)'''

# Cavetas when target language is Ada.
* It is not possible to reopen a namespace since the namespace is mapped agains Ada:s package.
* Identifiers are not case-sensetive as in C,C++,Java, ...

