package link_list

type Node struct {
	data string
	next *Node
}

type List struct {
	head *Node
	tail *Node
}

func (l *List) Head() *Node {
	return l.head
}

func (n *Node) String() string {
	return n.data
}

func (l *List) String() string {
	s := ""
	for current := l.Head(); current != nil; current = current.next {
		s += current.String() + " "
	}
	return s
}

func (l *List) Append(val string) {
	n := &Node{data: val}
	if l.head == nil {
		l.head = n
	}
	if l.tail != nil {
		l.tail.next = n
	}
	l.tail = n
}

func (l *List) Prepend(val string) {
	l.head = &Node{data: val, next: l.head}
	if l.tail == nil {
		l.tail = l.head
	}
}

func (n *Node) Reverse() *Node {
	if n == nil || n.next == nil {
		return n
	}

	newHead := n.next.Reverse()

	n.next.next = n
	n.next = nil
	return newHead
}

func (l *List) Reverse() {
	l.head, l.tail = l.head.Reverse(), l.head
}
