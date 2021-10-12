# read.py
# loading a file with open()

import numpy as np
resultados = open("resultados.txt", "r")

lines = 0

n = int(input("Número de processos: "))
r = int(input("Número de repeticoes: "))

# initialize array with counter for all processes
# in the end, every index of this array = r
process_counter = np.zeros(n)

print(process_counter)

# reading each line of the file and printing to the console
for line in resultados:
    lines+=1
    print(line[0])
    process_counter[int(line[0])] += 1

resultados.close()

print(process_counter)

if lines == n*r:
    print("\nNúmero de linhas correto!\n")
else:
    print("\nERRO: Número de linhas incorreto!\n")

if (process_counter == r).all():
    print("Todos os processos escreveram", r, "vezes")
else:
    print("ERRO: nem todos os processos escreveram", r, "vezes")
    print(process_counter)