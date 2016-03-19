package trees

import "../utils"

type BinaryTree struct {
	value int64
	left  Tree
	right Tree
}

func (tree *BinaryTree) NewNode(value int64) Tree {
	var left Tree
	var right Tree
	return &BinaryTree{value: value, left: left, right: right}
}

func (tree *BinaryTree) IsNull() bool {
	return tree == nil
}

func (tree *BinaryTree) Data() int64 {
	return tree.value
}

func (tree *BinaryTree) SetLeft(left Tree) {
	tree.left = left
}

func (tree *BinaryTree) SetRight(right Tree) {
	tree.right = right
}

func (tree *BinaryTree) Left() Tree {
	if tree == nil || tree.left == nil {
		var t Tree
		return t
	}
	return tree.left.(Tree)
}

func (tree *BinaryTree) Right() Tree {
	if tree == nil || tree.right == nil {
		var t Tree
		return t
	}
	return tree.right.(Tree)
}

func (tree *BinaryTree) TraverseDirection(value int64) Direction {
	if tree == nil || tree.IsNull() {
		return Root
	}

	if utils.MyRand(2) == 0 {
		return Left
	}

	return Right
}
