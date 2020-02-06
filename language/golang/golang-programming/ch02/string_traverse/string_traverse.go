package main

import "fmt"

func main() {
	str := "Hello,世界"

	for i := 0; i < len(str); i++ {
		fmt.Println(i, str[i])
	}
	fmt.Println()

	for i, ch := range str {
		fmt.Println(i, ch)
	}
}
