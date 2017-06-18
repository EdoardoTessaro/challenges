def condense(line, index):
  i = index+1
  while i < len(line) and line[i] != line[index-1]:
    i += 1
  if i == len(line):
    return None
  for j in range(1, i-index):
    if index-j-1 < 0 or line[i-j] != line[index-j-1]:
      return None
  return i

with open('input.txt') as f:
  for line in f:
    line = line.strip()
    prev_printed = 0
    for i in range(len(line)):
      if line[i] == ' ':
        I = condense(line, i)
        print(str(line[prev_printed:i]), end='')
        if I is not None:
          prev_printed = I+1
        else:
          prev_printed = i
    print(str(line[prev_printed:len(line)]))
