// Copyright 2015 Akshay Dixit
#include <iostream>
#include "gtest/gtest.h"
#include "../src/snametize.h"
#include "../src/writer/MetisWriter.h"

const std::string SMALL_WEBGRAPH("./small_webgraph.txt");
const std::string SMALLWEB_GRAPH_METIS("./small_webgraph.metis");
const std::string SMALLWEB_GRAPH_SNAP("./small_webgraph.snap");
const std::string SMALLWEB_GRAPH_GML("./small_webgraph.gml");

class SnametizeSmallTest : public ::testing::Test {
 protected:
    const std::string tmpFilePath = "tmpFile";
    SnametizeSmallTest() {
    }

    virtual ~SnametizeSmallTest() {
    }

    virtual void SetUp() {
    }

    virtual void TearDown() {
       std::remove(tmpFilePath.c_str());
    }
};

TEST_F(SnametizeSmallTest, TemporaryTest) {
    int i = 1;
    std::vector<uint64_t> v = {2, 3, 4};
    std::ofstream tmpFile(tmpFilePath);
    writeMetisLine(&tmpFile, v);
    EXPECT_EQ(1, i);
}
