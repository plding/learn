package main

import (
	"fmt"
	"golang.org/x/net/html"
	"os"
)

func main() {
	doc, err := html.Parse(os.Stdin)
	if err != nil {
		fmt.Fprintf(os.Stderr, "exercise_5.2: %v\n", err)
		os.Exit(1)
	}

	counts := make(map[string]int)
	visit(counts, doc)
	for node, count := range counts {
		fmt.Println(node, count)
	}
}

func visit(counts map[string]int, n *html.Node) {
	if n.Type == html.ElementNode {
		counts[n.Data]++
	}
	for c := n.FirstChild; c != nil; c = c.NextSibling {
		visit(counts, c)
	}
}
