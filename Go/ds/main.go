package main

import "fmt"

import "./trees"
import "./utils"

func main() {
	bt := (&trees.BinaryTree{}).NewNode(12)
	bst := (&trees.BinarySearchTree{}).NewNode(12)
	var i int64
	for i = 0; i < 20+utils.MyRand(20); i++ {
		val := utils.MyRand(1000)
		trees.Insert(bt, val)
		trees.Insert(bst, val)
	}
	fmt.Println(trees.InOrder(bt))
	fmt.Println(trees.InOrder(bst))
}
