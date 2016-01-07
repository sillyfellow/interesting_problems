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
	categ string
}

func MakeBinaryTree(value int) *BinaryTree {
	return &BinaryTree{data: value, categ: "bt"}
}

func (tree *BinaryTree) String() string {
	left_tree := ""
	if tree.left != nil {
		left_tree = tree.left.String()
	}

	right_tree := ""
	if tree.right != nil {
		right_tree = tree.right.String()
	}

	return fmt.Sprintf("%v %v (%v) %v", left_tree, tree.data, tree.categ, right_tree)
}

func (tree *BinaryTree) TraverseDirection(value int) Direction {
	if tree.data == value {
		return Root
	}

	if rand.Intn(2) == 0 {
		return Left
	}
	return Right
}

func (tree *BinaryTree) Insert(value int) *BinaryTree {
	direction := tree.TraverseDirection(value)
	if direction == Left {
		if tree.left == nil {
			tree.left = &BinaryTree{data: value, categ: "bt"}
		} else {
			tree.left = tree.left.Insert(value)
		}
	}

	if direction == Right {
		if tree.right == nil {
			tree.right = &BinaryTree{data: value, categ: "bt"}
		} else {
			tree.right = tree.right.Insert(value)
		}
	}
	return tree
}

func (tree *BinaryTree) Mirror() *BinaryTree {

	var lMirror *BinaryTree
	var rMirror *BinaryTree

	if tree.left != nil {
		lMirror = tree.left.Mirror()
	}

	if tree.right != nil {
		rMirror = tree.right.Mirror()
	}
	tree.left, tree.right = rMirror, lMirror
	return tree
}
