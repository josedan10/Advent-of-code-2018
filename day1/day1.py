# Part 1
inputFile = open("input.txt", "r")

calc = 0

# for line in inputFile:
#     calc += int(line)

# print("First answer " + calc)

# Part 2
from math import floor

frequencies = [0]
repeatedFrequency = False
inputList = inputFile.readlines()

while (not(repeatedFrequency)):

    for line in inputList:

        calc += int(line)

        print(calc)

        if (calc in frequencies): 
            print("El numero {} aparece en la lista de frecuencias anteriores".format(calc))
            repeatedFrequency = True
            break

        frequencies.append(calc)
        frequencies.sort()


print(len(frequencies))
