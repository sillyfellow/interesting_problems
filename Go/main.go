package main

import "fmt"
import "./link_list"

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

func main() {
	LLTest()
}
