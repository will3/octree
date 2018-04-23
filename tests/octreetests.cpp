#include "gtest/gtest.h"
#include "../octree.h"

TEST(Octree, SetValue) {
	Octree<int> tree;
	tree.set(1, 2, 3, 4);
	int result = tree.get(1, 2, 3);
	EXPECT_EQ(result, 4);
}

TEST(Octree, Default) {
	Octree<int> tree;
	EXPECT_EQ(tree.origin[0], 0);
	EXPECT_EQ(tree.origin[1], 0);
	EXPECT_EQ(tree.origin[2], 0);
}

TEST(Octree, SetValueChild) {
	Octree<int> tree(0, 0, 0, 1);
	tree.set(1, 2, 3, 4);
	int result = tree.get(1, 2, 3);
	EXPECT_EQ(result, 4);
	EXPECT_EQ(tree.children.size(), 8);
}

// TEST(ResizableOctree, SetValue) {
// 	ResizableOctree<int> tree;
// 	tree.set(0, 0, 0, 1);
// 	int result = tree.get(0, 0, 0);
// 	EXPECT_EQ(result, 1);	
// }

TEST(ResizableOctree, ExpandTree) {
	ResizableOctree<int> tree;
	tree.expandTree(true, true, true);
}

TEST(ResizableOctree, ExpandPositive) {
	ResizableOctree<int> tree;
	tree.set(33, 33, 33, 1);
	// int result = tree.get(33, 33, 33);
	// EXPECT_EQ(result, 1);

	// Octree<int> data = tree.data;
	// EXPECT_EQ(data.size, 64);
}

// TEST(ResizableOctree, ExpandNegative) {
// 	ResizableOctree<int> tree;
// 	tree.set(-1, -1, -1, 1);
// 	int result = tree.get(-1, -1, -1);
// 	EXPECT_EQ(result, 1);
// }