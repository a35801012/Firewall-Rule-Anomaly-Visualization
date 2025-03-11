f = open("f1.txt", "r+")
lines = f.readlines()
for line in lines:
    strlist = line.replace("yellow", "#fb9a99")
    for value in strlist:
        # print(value)
        with open("f2.txt", "a") as file1:
            file1.write(value)
