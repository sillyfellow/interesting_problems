package main

import "fmt"
import "./link_list"
import "./bin_tree"
import "math/rand"
import "time"

func LLTest() {
	list := new(link_list.List)
	list.Append("hello")
	list.Append("1")
	list.Append("2")
	list.Append("3")
	list.Append("World")
	list.Prepend("This!")
	list.Prepend("1")
	list.Prepend("2")
	list.Prepend("3")
	list.Prepend("4")
	list.Prepend("5")
	list.Prepend("6")
	list.Prepend("7")
	fmt.Printf("%v\n", list)
	list.Reverse()
	fmt.Printf("%v\n", list)
}

func BinaryTreeTest() {
	tree := bin_tree.MakeBinaryTree(36)
	for i := 0; i < 5; i++ {
		tree.Insert(rand.Intn(100))
	}
	fmt.Println(tree)

	tree = tree.Mirror()

	fmt.Println(tree)
}

func main() {
	rand.Seed(time.Now().UTC().UnixNano())
	LLTest()
	fmt.Println("Calling Binary Tree")
	BinaryTreeTest()
}
