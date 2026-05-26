#include <gtest/gtest.h>
#include "graph.h"

TEST(GraphTest, SumWeights) {
  Graph G;
  file_to_graph("small.txt", G);
  EdgeList mst = Kruskals(G);
  EXPECT_EQ(sum_weights(mst), 6);
}

TEST(GraphTest, SumWeightsSmall) {
  Graph G;
  file_to_graph("small.txt", G);
  EdgeList mst = Kruskals(G);
  EXPECT_EQ(sum_weights(mst), 6);
}

TEST(GraphTest, SumWeightsMedium) {
  Graph G;
  file_to_graph("medium.txt", G);
  EdgeList mst = Kruskals(G);
  EXPECT_EQ(sum_weights(mst), 11);
}

TEST(GraphTest, SumWeightsLarge) {
  Graph G;
  file_to_graph("large.txt", G);
  EdgeList mst = Kruskals(G);
  EXPECT_EQ(sum_weights(mst), 31);
}

TEST(GraphTest, SumWeightsLargest) {
  Graph G;
  file_to_graph("largest.txt", G);
  EdgeList mst = Kruskals(G);
  EXPECT_EQ(sum_weights(mst), 315);
}

TEST(GraphTest, MSTEdgeCountSmall) {
  Graph G;
  file_to_graph("small.txt", G);
  EdgeList mst = Kruskals(G);
  EXPECT_EQ((int)mst.size(), G.numVertices - 1);
}

TEST(GraphTest, MSTEdgeCountMedium) {
  Graph G;
  file_to_graph("medium.txt", G);
  EdgeList mst = Kruskals(G);
  EXPECT_EQ((int)mst.size(), G.numVertices - 1);
}

TEST(GraphTest, MSTEdgeCountLarge) {
  Graph G;
  file_to_graph("large.txt", G);
  EdgeList mst = Kruskals(G);
  EXPECT_EQ((int)mst.size(), G.numVertices - 1);
}

TEST(GraphTest, BFSVisitsAllSmall) {
  Graph G;
  file_to_graph("small.txt", G);
  VertexList result = bfs(G, 0);
  EXPECT_EQ((int)result.size(), G.numVertices);
}

TEST(GraphTest, BFSVisitsAllMedium) {
  Graph G;
  file_to_graph("medium.txt", G);
  VertexList result = bfs(G, 0);
  EXPECT_EQ((int)result.size(), G.numVertices);
}

TEST(GraphTest, BFSVisitsAllLarge) {
  Graph G;
  file_to_graph("large.txt", G);
  VertexList result = bfs(G, 0);
  EXPECT_EQ((int)result.size(), G.numVertices);
}

TEST(GraphTest, BFSStartsAtZero) {
  Graph G;
  file_to_graph("small.txt", G);
  VertexList result = bfs(G, 0);
  EXPECT_EQ(result[0], 0);
}

TEST(GraphTest, DFSVisitsAllSmall) {
  Graph G;
  file_to_graph("small.txt", G);
  VertexList result = dfs(G, 0);
  EXPECT_EQ((int)result.size(), G.numVertices);
}

TEST(GraphTest, DFSVisitsAllMedium) {
  Graph G;
  file_to_graph("medium.txt", G);
  VertexList result = dfs(G, 0);
  EXPECT_EQ((int)result.size(), G.numVertices);
}

TEST(GraphTest, DFSVisitsAllLarge) {
  Graph G;
  file_to_graph("large.txt", G);
  VertexList result = dfs(G, 0);
  EXPECT_EQ((int)result.size(), G.numVertices);
}

TEST(GraphTest, DFSStartsAtZero) {
  Graph G;
  file_to_graph("small.txt", G);
  VertexList result = dfs(G, 0);
  EXPECT_EQ(result[0], 0);
}

TEST(DisjointSetTest, MakeAndFind) {
  DisjointSet ds(5);
  EXPECT_EQ(ds.findSet(0), 0);
  EXPECT_EQ(ds.findSet(4), 4);
}

TEST(DisjointSetTest, UnionSets) {
  DisjointSet ds(5);
  ds.unionSets(0, 1);
  EXPECT_EQ(ds.findSet(0), ds.findSet(1));
}

TEST(DisjointSetTest, UnionSetsNotConnected) {
  DisjointSet ds(5);
  ds.unionSets(0, 1);
  EXPECT_NE(ds.findSet(0), ds.findSet(2));
}

TEST(DisjointSetTest, PathCompression) {
  DisjointSet ds(5);
  ds.unionSets(0, 1);
  ds.unionSets(1, 2);
  ds.unionSets(2, 3);
  EXPECT_EQ(ds.findSet(0), ds.findSet(3));
}

TEST(GraphTest, LoadSmall) {
  Graph G;
  file_to_graph("small.txt", G);
  EXPECT_EQ(G.numVertices, 4);
}

TEST(GraphTest, LoadMedium) {
  Graph G;
  file_to_graph("medium.txt", G);
  EXPECT_EQ(G.numVertices, 6);
}

TEST(GraphTest, LoadLarge) {
  Graph G;
  file_to_graph("large.txt", G);
  EXPECT_EQ(G.numVertices, 7);
}

TEST(GraphTest, LoadLargest) {
  Graph G;
  file_to_graph("largest.txt", G);
  EXPECT_EQ(G.numVertices, 100);
}
