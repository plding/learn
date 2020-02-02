package main

import (
    "fmt"
    "os"
    "strings"
    "bufio"
)

func main() {
    input := bufio.NewScanner(os.Stdin)
    for input.Scan() {
        fmt.Println(basename(input.Text()))
    }
}

func basename(s string) string {
    slash := strings.LastIndex(s, "/")
    s = s[slash+1:]
    if dot := strings.LastIndex(s, "."); dot >= 0 {
        s = s[:dot]
    }
    return s
}
