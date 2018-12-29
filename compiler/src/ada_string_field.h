// Protocol Buffers - Google's data interchange format
// Copyright 2008 Google Inc.  All rights reserved.
// http://code.google.com/p/protobuf/
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// Author: kenton@google.com (Kenton Varda)
// Author: jonp@google.com (Jon Perlow)
//  Based on original Protocol Buffers design by
//  Sanjay Ghemawat, Jeff Dean, and others.

#ifndef GOOGLE_PROTOBUF_COMPILER_JAVA_STRING_FIELD_H__
#define GOOGLE_PROTOBUF_COMPILER_JAVA_STRING_FIELD_H__

#include <map>
#include <string>

#include <ada_field.h>

namespace google {
namespace protobuf {
namespace compiler {
namespace ada {

class StringFieldGenerator : public FieldGenerator {
 public:
  explicit StringFieldGenerator(const FieldDescriptor* descriptor);
  ~StringFieldGenerator();
  
  // implements FieldGenerator ---------------------------------------
  void GenerateAccessorDeclarations(io::Printer* printer) const;
  void GenerateAccessorDefinitions(io::Printer* printer) const;
  void GenerateClearingCode(io::Printer* printer) const;
  void GenerateRecordComponentDeclaration(io::Printer* printer) const;
  void GenerateSerializeWithCachedSizes(io::Printer* printer) const;
  void GenerateByteSize(io::Printer* printer) const;
  void GenerateMergeFromCodedInputStream(io::Printer* printer) const;
  void GenerateMergingCode(io::Printer* printer) const;
  void GenerateStaticDefaults(io::Printer* printer) const;
  void GenerateFinalizationCode(io::Printer* printer) const;
 private: 
  const FieldDescriptor* descriptor_;
  map<string, string> variables_;

  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(StringFieldGenerator);
};

class RepeatedStringFieldGenerator : public FieldGenerator {
 public:
  explicit RepeatedStringFieldGenerator(const FieldDescriptor* descriptor);
  ~RepeatedStringFieldGenerator();

  // implements FieldGenerator ---------------------------------------
  void GenerateAccessorDeclarations(io::Printer* printer) const;
  void GenerateAccessorDefinitions(io::Printer* printer) const;
  void GenerateClearingCode(io::Printer* printer) const;
  void GenerateRecordComponentDeclaration(io::Printer* printer) const;
  void GenerateSerializeWithCachedSizes(io::Printer* printer) const;
  void GenerateByteSize(io::Printer* printer) const;
  void GenerateMergeFromCodedInputStream(io::Printer* printer) const;
  void GenerateMergingCode(io::Printer* printer) const;
  void GenerateStaticDefaults(io::Printer* printer) const;
  void GenerateFinalizationCode(io::Printer* printer) const;
 private:
  const FieldDescriptor* descriptor_;
  map<string, string> variables_;

  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(RepeatedStringFieldGenerator);
};

} // namespace java
} // namespace compiler
} // namespace protobuf
} // namespace google
#endif  // GOOGLE_PROTOBUF_COMPILER_JAVA_STRING_FIELD_H__