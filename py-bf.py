class Brainfuck:
  dataArray = [0] * 10
  now = 0

  def __init__ (self, string):
    self.string = string

    for element in enumerate(string):
      char = element[1]
      index = element[0]
      big = -1
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
    self.dataArray[self.now] -= 1
  
  def print (self):
    data = chr(self.dataArray[self.now])
    print(data, end='\n')
  def read (self):
    self.dataArray[self.now] = ord(input())
  
  def loop (self, beg):
    end = 0
    counterId = self.now

    hasIn = 0
    for element in enumerate(self.string[beg + 1 : ]):
      char = element[1]
      index = element[0]

      if char == '[':
        hasIn += 1
      elif char == ']':
        if hasIn == 0:
          end = index + beg + 1
        else:
          hasIn -= 1

    while self.dataArray[counterId] > 1:
      for element in enumerate(self.string[beg + 1 : end]):
        char = element[1]
        index = element[0]
        big = -1
        if index > big:
          big = self.do(char, index) - beg + 1

    return end
    
  def do (self, char, index):
    if char == '+':
      self.increment()
      return 0
    elif char == '-':
      self.decrement()
      return 0
    elif char == '>':
      self.moveRight()
      return 0
    elif char == '<':
      self.moveLeft()
      return 0
    elif char == '.':
      self.print()
      return 0
    elif char == ',':
      self.read()
      return 0      
    elif char == '[':
      return self.loop(index)
    else:
      return 0


