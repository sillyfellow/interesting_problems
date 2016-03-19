package trees

type BinarySearchTree struct {
	BinaryTree
}

func (tree *BinarySearchTree) NewNode(value int64) Tree {
	var left Tree
	var right Tree
	return &BinarySearchTree{BinaryTree{value: value, left: left, right: right}}
}

func (tree *BinarySearchTree) TraverseDirection(value int64) Direction {
	if tree == nil || tree.IsNull() {
		return Root
	}

	if value < tree.Data() {
		return Left
	}

	return Right
}
