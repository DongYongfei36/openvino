//*****************************************************************************
// Copyright 2017-2021 Intel Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//*****************************************************************************

#pragma once

#include "ngraph/output_vector.hpp"

namespace ngraph
{
    namespace onnx_import
    {
        namespace op
        {
            namespace set_1
            {
                inline OutputVector gather_elements(const Node& node)
                {
                    OutputVector ng_inputs{node.get_ng_inputs()};
                    auto data = ng_inputs.at(0);
                    auto indices = ng_inputs.at(1);
                    auto axis = node.get_attribute_value<int64_t>("axis", 0);

                    return {std::make_shared<ngraph::op::v6::GatherElements>(data, indices, axis)};
                }
            } // namespace set_1
        }     // namespace op
    }         // namespace onnx_import
} // namespace ngraph
