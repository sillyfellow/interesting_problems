package bin_tree

import "fmt"
import "math/rand"

type Direction int

const (
	Root = iota
	Left
	Right
)

type BinaryTree struct {
	data  int
	left  *BinaryTree
	right *BinaryTree
}

func EmptyTree() *BinaryTree {
	return nil
}

func (tree *BinaryTree) String() string {

	if tree == nil {
		return ""
	}

	return fmt.Sprintf("%v - %v - %v", tree.left.String(), tree.data, tree.right.String())
}

func (tree *BinaryTree) TraverseDirection(value int) Direction {
	if tree == nil || tree.data == value {
		return Root
	}

	if rand.Intn(2) == 0 {
		return Left
	}
	return Right
}

func (tree *BinaryTree) Insert(value int) *BinaryTree {
	if tree == nil {
		return &BinaryTree{data: value}
	}

	direction := tree.TraverseDirection(value)

	if direction == Left {
		tree.left = tree.left.Insert(value)
	}

	if direction == Right {
		tree.right = tree.right.Insert(value)
	}
	return tree
}

func (tree *BinaryTree) Mirror() *BinaryTree {
	if tree == nil {
		return nil
	}

	tree.left, tree.right = tree.right.Mirror(), tree.left.Mirror()
	return tree
}
