package main

import "fmt"
import "./link_list"

func LLTest() {
	list := new(link_list.List)
	list.Append("hello")
	list.Append("World")
	list.Prepend("This!")
	fmt.Printf("%v", list)
}

func main() {
	LLTest()
}
