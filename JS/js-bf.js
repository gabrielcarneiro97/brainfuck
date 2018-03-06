class Brainfuck {
  constructor (string) {
    this.dataArray = new Array(30000).fill(0)
    this.charArray = string.split('')
    this.now = 0

    for (let i = 0; i < this.charArray.length; i++) {
      let char = this.charArray[i]
      i = this.do(char, i)
    }
  }

  moveRight () {
    this.now += 1
  }
  moveLeft () {
    if (this.now > 0) {
      this.now -= 1
    }
  }

  increment () {
    this.dataArray[this.now] += 1
  }
  decrement () {
    if (this.dataArray[this.now] > 0) {
      this.dataArray[this.now] -= 1
    }
  }

  print () {
    process.stdout.write(String.fromCharCode(this.dataArray[this.now]))
  }
  read () {

  }

  loop (beg) {
    let end = 0

    let hasIn = 0
    for (let i = beg + 1; i < this.charArray.length; i++) {
      let char = this.charArray[i]

      if (char === '[') {
        hasIn += 1
      } else if (char === ']') {
        if (hasIn === 0) {
          end = i
          break
        } else {
          hasIn -= 1
        }
      }
    }
    while (this.dataArray[this.now] > 0) {
      for (let i = beg + 1; i < end; i++) {
        let char = this.charArray[i]
        i = this.do(char, i)
      }
    }
    return end
  }

  do (char, index) {
    switch (char) {
      case '+':
        this.increment()
        return index
      case '-':
        this.decrement()
        return index
      case '>':
        this.moveRight()
        return index
      case '<':
        this.moveLeft()
        return index
      case '.':
        this.print()
        return index
      case '[':
        return this.loop(index)
      default:
        return index
    }
  }
}

let b = new Brainfuck('++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.')
