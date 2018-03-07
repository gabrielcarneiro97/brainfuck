class Brainfuck
  def initialize(string)
    @string = string
    @data_array = Array.new(30000, 0)
    @now = 0

    ret = 0
    for i in 0..string.length-1
      char = string[i]


      next if i != ret
      ret = self.do(char, i)

      if ret == i
        ret += 1
      end

    end
  end

  def move_right
    @now += 1
  end

  def move_left
    if @now > 0
      @now -= 1
    end
  end

  def increment
    @data_array[@now] += 1
  end

  def decrement
    if @data_array[@now] > 0
      @data_array[@now] -= 1
    end
  end

  def print!
    print @data_array[@now].chr
  end

  def read
    data = gets.chomp
    @data_array[@now] = data[0].ord
  end

  def loop(beg)
    final = 0

    hasIn = 0

    for i in beg + 1..@string.length - 1
      char = @string[i]

      if char == '['
        hasIn += 1
      elsif char == ']'
        if hasIn == 0
          final = i
          break
        else
          hasIn -= 1
        end
      end
    end

    while @data_array[@now] > 0
      ret = beg + 1
      for i in beg + 1..final
        char = @string[i]
        next if i != ret
      
        ret = self.do(char, i)
        if ret == i
          ret += 1
        end
      end
    end

    return final
  end

  def do(char, index)
    case char
    when '+'
      self.increment
      return index
    when '-'
      self.decrement
      return index
    when '>'
      self.move_right
      return index
    when '<'
      self.move_left
      return index
    when ','
      self.read
      return index
    when '.'
      self.print!
      return index
    when '['
      return self.loop(index)
    else
      return index
    end
  end

end

t = Brainfuck.new("++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.")
