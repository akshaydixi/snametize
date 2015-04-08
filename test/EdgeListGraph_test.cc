// Copyright 2015 Akshay Dixit

#include "../src/graph/EdgeListGraph.h"
#include "gtest/gtest.h"
#include <iostream>

class EdgeListGraphTest : public ::testing::Test {
 protected:
    EdgeListGraphTest() {
    }

    virtual ~EdgeListGraphTest() {
    }

    virtual void SetUp() {
        this->mySmallGraph = new EdgeListGraph(false, false);
        this->mySmallGraph->addEdge(1, 2);
        this->mySmallGraph->addEdge(2, 3);
        this->mySmallGraph->addEdge(3, 4);
        this->mySmallGraph->addEdge(4, 5);
        this->mySmallGraph->addEdge(1, 1);
    }

    virtual void TearDown() {
        delete this->mySmallGraph;
    }

 public:
    EdgeListGraph* testGraph;
    EdgeListGraph* mySmallGraph;
};

TEST_F(EdgeListGraphTest, CheckAddEdge) {
    testGraph = new EdgeListGraph(false, false);
    testGraph->addEdge(1,1);
    EXPECT_EQ(testGraph->getVertexCount(), 0);
    testGraph->addEdge(1,2);
    EXPECT_EQ(1, testGraph->getEdgeCount());
    delete testGraph;
}

TEST_F(EdgeListGraphTest, CheckEdgeCount) {
    EXPECT_EQ(4, mySmallGraph->getEdgeCount());
}

TEST_F(EdgeListGraphTest, CheckVertexCount) {
    EXPECT_EQ(5, mySmallGraph->getVertexCount());
}



