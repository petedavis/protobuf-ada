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

#include <set>
#include <map>
#include <ada_enum.h>
#include <ada_helpers.h>
#include <google/protobuf/io/printer.h>
#include <google/protobuf/stubs/strutil.h>
#include <algorithm>

namespace google {
  namespace protobuf {
    namespace compiler {
      namespace ada {
	using namespace std;
	namespace {

	  bool EnumConstantOrderingByValue(const EnumValueDescriptor *a,
					   const EnumValueDescriptor *b) {
	      return a->number() < b->number();
	  };

	  // Sort the fields of the given EnumDescriptor by value into a new[]'d array
	  // and return it.


          const std::vector<const EnumValueDescriptor*> SortEnumConstantsByValue2(const EnumDescriptor* enum_descriptor) {
	    std::vector<const EnumValueDescriptor*> ordered_values;

	    for (int i = 0; i < enum_descriptor->value_count(); i++) {
	      ordered_values.push_back(enum_descriptor->value(i));
	    }
	    std::sort(ordered_values.begin(),
		      ordered_values.end(),
		      EnumConstantOrderingByValue);
	    return ordered_values;
	  }
	}

	// =========================================================================================
	EnumGenerator::EnumGenerator(const EnumDescriptor* descriptor)
	: descriptor_(descriptor) { }

	// =========================================================================================
	EnumGenerator::~EnumGenerator() { }

	// =========================================================================================
	void EnumGenerator::GenerateDefinition(io::Printer* printer) {
	  // Ada requires that enumeration constant values are defined in an ascending
	  // order. We must therefore sort enumeration constants by value.
	  std::vector<const EnumValueDescriptor*> ordered_values = SortEnumConstantsByValue2(descriptor_);
	  std::map<std::string, std::string> vars;

	  vars["name"] = descriptor_->name();
	  printer->Print(vars,"type $name$ is (");
	  for (int i = 0; i < descriptor_->value_count(); i++) {
	    vars["literal"] = ordered_values[i]->name();
	    printer->Print(vars,"$literal$" );

	    // More enumeration literals follow?
	    if (i != descriptor_->value_count() - 1) {
	      printer->Print(vars,", ");
	    }
	  }
	  printer->Print(vars,");\n");
          vars["name"] = EnumTypeName(descriptor_, false);
	  printer->Print(vars,"for $name$'Size use 32;\n");
          vars["name"] = descriptor_->name();
	  printer->Print(vars, "for $name$ use (");
	  for (int i = 0; i < descriptor_->value_count(); i++) {
	    vars["constant"]= ordered_values[i]->name();
	    vars["value"]= SimpleItoa(ordered_values[i]->number());
	    printer->Print(vars,"$constant$ => $value$");

	    // More constants follow?
	    if (i != descriptor_->value_count() - 1) {
	      printer->Print(vars,", ");
	    }
	  }
	  printer->Print(vars,");\n");
          vars["name"] = EnumTypeName(descriptor_, false);
	  printer->Print(vars,
			 "function Enumeration_To_PB_Int32 is new Ada.Unchecked_Conversion ($name$, Google.Protobuf.Wire_Format.PB_Int32);\n"
			 "function PB_Int32_To_Enumeration is new Ada.Unchecked_Conversion (Google.Protobuf.Wire_Format.PB_Int32, $name$);\n");
	}


      } // namespace ada
    } // namespace compiler
  } // namespace protobuf
} // namespace google
