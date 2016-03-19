package trees

import "fmt"

type Direction int64

const (
	Root = iota
	Left
	Right
)

type Tree interface {
	Data() int64
	Left() Tree
	Right() Tree
	IsNull() bool
	SetLeft(left Tree)
	SetRight(right Tree)
	NewNode(value int64) Tree
	TraverseDirection(value int64) Direction
}

func InOrder(tree Tree) string {
	if tree == nil || tree.IsNull() {
		return ""
	}
	return fmt.Sprintf("%v - %v - %v", InOrder(tree.Left()), tree.Data(), InOrder(tree.Right()))
}

func Insert(tree Tree, value int64) Tree {
	if tree.IsNull() {
		return tree.NewNode(value)
	}

	direction := tree.TraverseDirection(value)

	if direction == Left {
		if tree.Left() == nil {
			tree.SetLeft(tree.NewNode(value))
		} else {
			tree.SetLeft(Insert(tree.Left(), value))
		}
	}

	if direction == Right {
		if tree.Right() == nil {
			tree.SetRight(tree.NewNode(value))
		} else {
			tree.SetRight(Insert(tree.Right(), value))
		}
	}
	return tree
}
