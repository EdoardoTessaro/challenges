from random import random
import math

def randRound(x):
  """Rounds x up or down randomly, but weighed by x's decimal value.
    E.g., if x == 10.2, there will be a 20% chance for x to become 11
    and a 80% chance to be truncated to 10.
  """
  r = random()      #random float from 0.0 to 1.0
  dec = x - int(x)  #decimal part of x
  if r > dec:
    x = math.floor(x)
  else:
    x = math.ceil(x)
  return x

def step(S, I, R, si_rate, ir_rate, sr_rate):
  """Computes one step into the simulation, returns the updated
    population sizes. If the predicted population size isn't an integer,
    we choose whether to round up or down at random (see randRound()
    above).
    Precautions are taken to keep the total population constant.
  """
  infected = randRound(S*si_rate)       #Sane -> Infected
  S = S - infected
  vaccinated = randRound(S*sr_rate)     #Sane -> Recovered
  recovered = randRound(I*ir_rate)      #Infected -> Recovered
  S = S - vaccinated
  I = I + infected - recovered
  R = R + recovered + vaccinated
  return (S, I, R)

def printPopulation(S, I, R):
  print('S: {:05.2f}%, I: {:05.2f}%, R: {:05.2f}%'.format(float(S*100)/N, float(I*100)/N, float(R*100)/N))
  

#PARAMETERS
SIMULATION_STEPS = 1000

filename = input("Insert the input file's name [input1.txt | input2.txt]: ").strip()
if filename == '':
  filename = 'input1.txt'
if filename == 'input1.txt':
  with open(filename) as f:
    for line in f:
      N, I, si_rate, ir_rate, sr_rate = list(map(float, line.strip().split(' ')))
      S = N - I
      R = 0
      for s in range(SIMULATION_STEPS):
        printPopulation(S, I, R)
        if I == 0:
          break
        S, I, R = step(S, I, R, si_rate, ir_rate, sr_rate)
      print()
elif filename == 'input2.txt':
  with open(filename) as f:
    N, I, next_si, next_ir, next_sr = list(map(float, list(f)[0].strip().split(' ')))
    S = N - I
    R = 0
    file_index = 0
    next_step = 0
    for s in range(SIMULATION_STEPS):
      if s == next_step:
        si_rate = next_si
        ir_rate = next_ir
        sr_rate = next_sr
        file_index += 1
        if len(list(f)) > file_index:
          next_step, next_si, next_ir, next_sr = list(map(float, list(f)[file_index].strip().split(' ')))
      printPopulation(S, I, R)
      if I == 0:
        break
      S, I, R = step(S, I, R, si_rate, ir_rate, sr_rate)
        
