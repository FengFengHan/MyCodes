import random
def valid(Sort):
    success = True
    for i in range(100):
        x = []
        for j in range(6):
            x.append(random.randrange(10))
        y = x[:]
        Sort(x)
        if not x == sorted(y):
            success = False
            print("x:")
            print(y)
            print("sort(x):")
            print(x)
    if success:
        print("Success!")

