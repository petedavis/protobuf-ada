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
//  Based on original Protocol Buffers design by
//  Sanjay Ghemawat, Jeff Dean, and others.

#ifndef GOOGLE_PROTOBUF_COMPILER_ADA_FIELD_H__
#define GOOGLE_PROTOBUF_COMPILER_ADA_FIELD_H__

#include <map>
#include <string>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/stubs/common.h>
#include <google/protobuf/io/printer.h>

namespace google {

  namespace protobuf {
    namespace compiler {
      namespace ada {
	using namespace std;

	// Helper function: set variables in the map that are the same for all
	// field code generators.
	// ['name', 'index', 'number', 'packagename', 'declared_type', 'tag_size'].
	void SetCommonFieldVariables(const FieldDescriptor* descriptor,
				     std::map<string, string>* variables);

	class FieldGenerator {
	  public:

	  FieldGenerator() { }
	  virtual ~FieldGenerator();

	  // Generate declarations for all of the accessor functions related to this
	  // field.  These are placed inside the package specification.
	  virtual void GenerateAccessorDeclarations(io::Printer* printer) const = 0;

	  // Generate definitions for all of the accessor functions related to this
	  // field.
	  virtual void GenerateAccessorDefinitions(io::Printer* printer) const = 0;

	  // Generate lines of code (statements, not declarations) which clear the
	  // field.  This is used to define the clear_$name$() method as well as
	  // the Clear() method for the whole message.
	  virtual void GenerateClearingCode(io::Printer* printer) const = 0;

	  // Generate a declaration for this field inside the Ada tagged record type
	  // used to store fields.
	  virtual void GenerateRecordComponentDeclaration(io::Printer* printer) const = 0;

	  // Generate lines to serialize this field, which are placed within the
	  // message's Serialize_With_Cached_Sizes procedure.
	  virtual void GenerateSerializeWithCachedSizes(io::Printer* printer) const = 0;

	  // Generate lines to compute the serialized size of this field, which
	  // are placed in the message's Byte_Size function.
	  virtual void GenerateByteSize(io::Printer* printer) const = 0;

	  // Generate lines to decode this field, which will be placed inside the
	  // message's MergeFromCodedInputStream procedure.
	  virtual void GenerateMergeFromCodedInputStream(io::Printer* printer) const = 0;

	  // Generate lines of code (statements, not declarations) which merges the
	  // contents of the field from the current message to the target message,
	  // which is stored in the generated code variable "from".
	  // This is used to fill in the MergeFrom method for the whole message.
	  // Details of this usage can be found in ada_message.cc under the
	  // GenerateMergeFrom method.
	  virtual void GenerateMergingCode(io::Printer* printer) const = 0;

	  // Generate "static" defaults
	  virtual void GenerateStaticDefaults(io::Printer* printer) const = 0;

	  // Generate lines to decode this field from a packed value, which will be
	  // placed inside the message's Merge_From_Coded_Input_Stream method.
	  virtual void GenerateMergeFromCodedInputStreamWithPacking(io::Printer* printer) const;

	  // Generate any code that needs to go in the Finalize procedure for cleanup.
	  // Most field types don't need this, so the default implementation is empty.
	  virtual void GenerateFinalizationCode(io::Printer* printer) const { }

	  // Generate functions renaming enumeration literats
	  virtual void GenerateEnumerationLiteralRenaming(io::Printer* printer) const { }

	  private:
	  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(FieldGenerator);
	};

	// Convenience class which constructs FieldGenerators for a Descriptor.

	class FieldGeneratorMap {
	  public:
	  explicit FieldGeneratorMap(const Descriptor* descriptor);
	  ~FieldGeneratorMap();

	  const FieldGenerator& get(const FieldDescriptor* field) const;

	  private:
	  const Descriptor* descriptor_;
	  std::vector<unique_ptr<FieldGenerator>> field_generators_;

	  static FieldGenerator* MakeGenerator(const FieldDescriptor* field);

	  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(FieldGeneratorMap);
	};

      } // namespace ada
    } // namespace compiler
  } // namespace protobuf
} // namespace google

#endif // GOOGLE_PROTOBUF_COMPILER_ADA_FIELD_H__
