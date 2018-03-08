use std::io;

struct Brainfuck {
    now : usize,
    string : String,
    data_array : [usize;30000],
}

impl Brainfuck {
    fn new (string : &str) -> Brainfuck {
        Brainfuck {
            now: 0,
            string: string.to_string(),
            data_array: [0;30000],
        }
    }

    fn exec (&mut self) {
        let chars = self.string.clone();

        let mut nxt = 0;
        for (i, _) in chars.chars().enumerate() {
            
            if i == nxt {
                nxt = self.do_it(nxt);
            }
        }
    }

    fn move_right (&mut self) {
        self.now += 1;
    }
    fn move_left (&mut self) {
        if self.now > 0 {
            self.now -= 1;
        }
    }

    fn increment (&mut self) {
        self.data_array[self.now] += 1;
    }
    fn decrement (&mut self) {
        if self.data_array[self.now] > 0 {
            self.data_array[self.now] -= 1;
        }
    }

    fn print (&self) {
        print!("{}", self.data_array[self.now] as u8 as char);
    }
    fn read (&mut self) {
        let mut string = String::new();
        io::stdin().read_line(&mut string)
            .expect("Failed to read line");
        
        self.data_array[self.now] = match string.chars().next() {
            Some(c) => c as usize,
            None => 0,
        };
    }

    fn loopy (&mut self, beg : usize) -> usize {

        let mut has_in = 0;
        let mut end = beg;

        let chars = self.string.clone();

        for (i, c) in chars.chars().enumerate() {
            if i > beg {
                match c {
                    ']' => {
                        if has_in == 0 {
                            end = i;
                            break;
                        } else {
                            has_in -= 1;
                        }
                    },
                    '[' => {
                        has_in += 1;
                    },
                    _ => ()
                }
            }
        };

        while self.data_array[self.now] > 0 {

            let mut nxt = beg + 1;

            for (i, _) in chars.chars().enumerate() {
               if i > beg && i < end {
                   if i == nxt {
                       nxt = self.do_it(nxt);                   
                   }
               }
           }
        }

        end
    }

    fn do_it (&mut self, index : usize) -> usize {

        let c = String::from(&self.string[index..index+1]);

        let c = match c.chars().next() {
            Some(c) => c as char,
            None => ' ' as char
        };

        match c {
            '+' => {
                self.increment();
                index + 1
            },
            '-' => {
                self.decrement();
                index + 1
            },
            '>' => {
                self.move_right();
                index + 1
            },
            '<' => {
                self.move_left();
                index + 1
            },
            ',' => {
                self.read();
                index + 1
            },
            '.' => {
                self.print();
                index + 1
            },
            '[' => {
                self.loopy(index)
            },
            _ => index + 1
        }
    }
}


fn main() {
    Brainfuck::new("++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.").exec();
}