n = int(input())
mylist = []
for i in range(0, n):
    mylist.append(int(input()))
mylist.sort()

for x in mylist:
    print("%d"%x)