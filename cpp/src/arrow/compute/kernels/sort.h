// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.

#pragma once

#include <memory>

#include "arrow/compute/kernel.h"
#include "arrow/status.h"
#include "arrow/util/visibility.h"

namespace arrow {

class Array;

namespace compute {

class FunctionContext;

ARROW_EXPORT
Status Sort(FunctionContext* ctx, const Array& values, std::shared_ptr<Array>* offsets);

ARROW_EXPORT
Status Sort(FunctionContext* ctx, const Datum& values, Datum* offsets);

class ARROW_EXPORT SortKernel : public UnaryKernel {
 protected:
  std::shared_ptr<DataType> type_;

 public:
  explicit SortKernel(const std::shared_ptr<DataType>& type) : type_(type) {}

  Status Call(FunctionContext* ctx, const Datum& values, Datum* offsets) override = 0;

  std::shared_ptr<DataType> out_type() const override { return type_; }

  virtual Status Sort(FunctionContext* ctx, const std::shared_ptr<Array>& values,
                      std::shared_ptr<Array>* offsets) = 0;

  static Status Make(const std::shared_ptr<DataType>& value_type,
                     std::unique_ptr<SortKernel>* out);
};

}  // namespace compute
}  // namespace arrow
