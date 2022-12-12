import random

D = list(input("Enter k bit message: "))
P = list(input("Enter p bit CRC pattern: "))

# D = list(str(11100011))
# P = list(str(110011))
D = [int(i) for i in D]
P = [int(i) for i in P]


def long_div(quotient, P):
    # p = len(P)
    remainder = [quotient[i] ^ P[i] for i in range(len(P))]
    for i in range(len(P), len(quotient)):
        # print(remainder)
        # print(remainder)
        if(remainder[0] == 0):
            remainder.append(quotient[i])
            remainder.pop(0)
            continue
        for j in range(len(P)):
            remainder[j] = remainder[j] ^ P[j]
        remainder.append(quotient[i])
        remainder.pop(0)
    return remainder


quotient = D
for i in range(len(P)-1):
    quotient.append(0)
remainder = long_div(quotient, P)
print("Remainder  ",remainder)
print("CRC pattern is: ", end="")
# if(remainder[0] == 0):
#     for i in range(1, len(remainder)):
#         print(remainder[i], end="")
#     print()


def generate_error(D):
    rand = random.randint(0, len(D)-1)
    D[rand] = 1-D[rand]
    return D


new_D = generate_error(D)
for i in range(1, len(remainder)):
    new_D.append(remainder[i])

new_remainder = long_div(new_D, P)
print(new_remainder)
print("New Frame is ", "".join(str(i) for i in new_D))
if 1 in new_remainder:
    print("Frame Discarded")
else:
    print("Frame Accepted")
