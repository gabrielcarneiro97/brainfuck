class Brainfuck:
  dataArray = [0] * 30000
  now = 0

  def __init__ (self, string):
    self.string = string

    big = -1
    for element in enumerate(string):
      char = element[1]
      index = element[0]
      if index > big:
        big = self.do(char, index)
  
  def moveRight (self):
    self.now += 1

  def moveLeft (self):
    if self.now > 0:
      self.now -= 1
  
  def increment (self):
    self.dataArray[self.now] += 1

  def decrement (self):
    if self.dataArray[self.now] - 1 > 0:
      self.dataArray[self.now] -= 1
    else:
      self.dataArray[self.now] = 0
  
  def print (self):
    data = chr(self.dataArray[self.now])
    print(data, end='')

  def read (self):
    self.dataArray[self.now] = ord(input())
  
  def loop (self, beg):
    end = 0

    hasIn = 0
    for element in enumerate(self.string[beg + 1 : ]):
      char = element[1]
      index = element[0]

      if char == '[':
        hasIn += 1
      elif char == ']':
        if hasIn == 0:
          end = index + beg + 1
          break
        else:
          hasIn -= 1

    while self.dataArray[self.now] > 0:
      big = -1
      for element in enumerate(self.string[beg + 1 : end]):
        char = element[1]
        index = element[0]
        if index + beg + 1 > big:
          big = self.do(char, index + beg + 1)

    return end
    
  def do (self, char, index):
    if char == '+':
      self.increment()
      return index
    elif char == '-':
      self.decrement()
      return index
    elif char == '>':
      self.moveRight()
      return index
    elif char == '<':
      self.moveLeft()
      return index
    elif char == '.':
      self.print()
      return index
    elif char == ',':
      self.read()
      return index
    elif char == '[':
      return self.loop(index)
    else:
      return index

b = Brainfuck('++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.')

