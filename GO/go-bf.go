package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
)

type bf struct {
	dataArray [30000]int
	str       string
	now       int
}

func moveRight(data bf) bf {
	data.now++
	return data
}
func moveLeft(data bf) bf {
	if data.now > 0 {
		data.now--
	}
	return data
}

func increment(data bf) bf {
	data.dataArray[data.now]++
	return data
}
func decrement(data bf) bf {
	if data.dataArray[data.now] > 0 {
		data.dataArray[data.now]--
	}
	return data
}

func print(data bf) bf {
	str := strconv.QuoteRune(rune(data.dataArray[data.now]))
	fmt.Printf("%s", str[1:len(str)-1])
	return data
}

func read(data bf) bf {
	reader := bufio.NewReader(os.Stdin)
	ch, _ := reader.ReadString('\n')
	i := int([]rune(ch)[0])

	data.dataArray[data.now] = i

	return data
}

func loop(data bf, index int) (bf, int) {
	beg := index
	var end int
	leng := len(data.str)

	hasIn := 0

	for i := beg + 1; i < leng; i++ {
		char := string([]rune(data.str)[i])

		if char == "[" {
			hasIn++
		} else if char == "]" {
			if hasIn == 0 {
				end = i
				break
			} else {
				hasIn--
			}
		}
	}

	for data.dataArray[data.now] > 0 {
		for i := beg + 1; i < end; i++ {
			char := string([]rune(data.str)[i])

			data, i = doIt(char, i, data)
		}
	}

	return data, end
}

func doIt(char string, index int, data bf) (bf, int) {
	switch char {
	case "+":
		return increment(data), index
	case "-":
		return decrement(data), index
	case ">":
		return moveRight(data), index
	case "<":
		return moveLeft(data), index
	case ".":
		return print(data), index
	case ",":
		return read(data), index
	case "[":
		return loop(data, index)
	default:
		return data, index
	}
}

func brainfuck(str string) {
	var data bf

	data.str = str

	for index := 0; index < len(data.str); index++ {
		char := string([]rune(data.str)[index])
		data, index = doIt(char, index, data)
	}
}

func main() {
	str := "++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++."
	brainfuck(str)
}
