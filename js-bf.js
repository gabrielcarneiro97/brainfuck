
var dataArray = []
var charArray = []
var now = 0

const string = '[ > [ >+ >+ << -] >> [- << + >>] <<< -] >>.'
charArray = string.split('')

const moveLeft = () => { now = now - 1 < 0 ? 0 : now - 1 }
const moveRight = () => { now++ }
const increment = () => {
  if (isNaN(dataArray[now])) {
    dataArray[now] = 1
  } else {
    dataArray[now]++
  }
}
const decrement = () => {
  if (isNaN(dataArray[now])) {
    dataArray[now] = 1
  } else {
    dataArray[now]--
  }
}
const findLoopEnd = (beg) => {
  let haveIn = 0
  for (let charId = beg + 1; charId < charArray.length; charId++) {
    let char = charArray[charId]
    if (char === '[') {
      haveIn++
    } else if (char === ']') {
      if (haveIn !== 0) {
        haveIn--
      } else {
        return charId
      }
    }
  }
}
const loop = (charId) => {
  let counterId = now
  let beg = charId
  let end = findLoopEnd(beg)
  while (dataArray[counterId] !== 0) {
    for (let count = beg + 1; count < end; count++) {
      doIt(charArray[count], count)
    }
  }
  return end + 1
}
const print = () => { console.log(String.fromCharCode(dataArray[now])) }

const doIt = (char, charId) => {
  switch (char) {
    case '+':
      increment()
      return charId
    case '-':
      decrement()
      return charId
    case '>':
      moveRight()
      return charId
    case '<':
      moveLeft()
      return charId
    case '.':
      print()
      return charId
    case '[':
      return loop(charId)
    default:
      return charId
  }
}

for (let charId = 0; charId < charArray.length; charId++) {
  let char = charArray[charId]
  charId = doIt(char, charId)
}
