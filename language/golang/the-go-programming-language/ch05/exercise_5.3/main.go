package main

import (
	"fmt"
	"golang.org/x/net/html"
	"os"
	"strings"
)

func main() {
	doc, err := html.Parse(os.Stdin)
	if err != nil {
		fmt.Fprintf(os.Stderr, "exercise_5.3: %v\n", err)
		os.Exit(1)
	}
	visit(doc)
}

func visit(n *html.Node) {
	if n.Data != "script" && n.Data != "style" {
		for c := n.FirstChild; c != nil; c = c.NextSibling {
			if c.Type == html.ElementNode {
				visit(c)
			} else if c.Type == html.TextNode {
				text := strings.Trim(c.Data, " \t\r\n")
				if text != "" {
					fmt.Println(text)
				}
			}
		}
	}
}
