import os
import random

for i in range(1000):

    option = "//"  # + - * //

    f1 = open("out.txt","r")
    f2 = open("in.txt","w")
    a = random.randint(100000000000000000000,10000000000000000000000000000000000)
    b = random.randint(1,100000000000000000000)
    f2.write("{} {}".format(a,b))
    f2.close()
    os.system("main.exe {}".format(option))

    out = int(f1.readline())
    ans = eval(str(a) + option + str(b))

    if ans != out:
        print("answer {} {} {} is not valid, requires {}, but outputs {}".format(a,option,b,ans,out))
        exit(0)
    else:
        print("answer {} valid".format(i))

    f1.close()