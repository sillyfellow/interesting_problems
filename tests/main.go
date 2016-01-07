package main

import "fmt"

type Cloneable interface {
	Clone()
}

type BaseClass struct {
	name string
}

type Derived struct {
	BaseClass
}

func (c *BaseClass) PrintName() {
	fmt.Println(c.name)
}

func (c *BaseClass) Clone() {
	cc := c.Dup(c.name)
	cc.PrintName()
	fmt.Println("Called")
}

func (c *Derived) Clone() {
	cc := c.Dup(c.name)
	cc.PrintName()
	fmt.Println("Called")
}

func (c *BaseClass) Dup(name string) *BaseClass {
	return &BaseClass{name: "bbaase" + name}
}

func (c *Derived) Dup(name string) *Derived {
	return &Derived{BaseClass{name: "derived" + name}}
}

func main() {

	animal := &BaseClass{name: "base"}
	dog := &Derived{BaseClass{name: "dog"}}

	animal.PrintName()
	dog.PrintName()

	animal.Clone()
	dog.Clone()

	//aC.PrintName()
	//dC.PrintName()
}
