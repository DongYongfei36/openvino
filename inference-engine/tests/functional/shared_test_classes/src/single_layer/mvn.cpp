// Copyright (C) 2020 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
//

#include "shared_test_classes/single_layer/mvn.hpp"

namespace LayerTestsDefinitions {

std::string MvnLayerTest::getTestCaseName(testing::TestParamInfo<mvnParams> obj) {
    InferenceEngine::SizeVector inputShapes;
    InferenceEngine::Precision inputPrecision;
    bool acrossChannels, normalizeVariance;
    double eps;
    std::string targetDevice;
    std::tie(inputShapes, inputPrecision, acrossChannels, normalizeVariance, eps, targetDevice) = obj.param;
    std::ostringstream result;
    result << "IS=" << CommonTestUtils::vec2str(inputShapes) << "_";
    result << "Precision=" << inputPrecision.name() << "_";
    result << "AcrossChannels=" << (acrossChannels ? "TRUE" : "FALSE") << "_";
    result << "NormalizeVariance=" << (normalizeVariance ? "TRUE" : "FALSE") << "_";
    result << "Epsilon=" << eps << "_";
    result << "TargetDevice=" << targetDevice;
    return result.str();
}

void MvnLayerTest::SetUp() {
    InferenceEngine::SizeVector inputShapes;
    InferenceEngine::Precision inputPrecision;
    bool acrossChanels, normalizeVariance;
    double eps;
    std::tie(inputShapes, inputPrecision, acrossChanels, normalizeVariance, eps, targetDevice) = this->GetParam();
    auto inType = FuncTestUtils::PrecisionUtils::convertIE2nGraphPrc(inputPrecision);
    auto param = ngraph::builder::makeParams(inType, {inputShapes});
    auto paramOuts = ngraph::helpers::convert2OutputVector(ngraph::helpers::castOps2Nodes<ngraph::op::Parameter>(param));
    auto mvn = std::dynamic_pointer_cast<ngraph::op::MVN>(ngraph::builder::makeMVN(paramOuts[0], acrossChanels, normalizeVariance, eps));
    ngraph::ResultVector results{std::make_shared<ngraph::opset1::Result>(mvn)};
    function = std::make_shared<ngraph::Function>(results, param, "mvn");
}
}  // namespace LayerTestsDefinitions