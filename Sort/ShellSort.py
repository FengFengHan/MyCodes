import random

def ShellSort(lists):
    n = len(lists)
    dlta = []
    t = 2
    while t <= n:
        dlta.append(t-1)
        t *= 2
    for i in range(len(dlta)-1,-1,-1):
        ShellInsert(lists,dlta[i])

def ShellInsert(lists, k):
    for i in range(k):
        for j in range(i+k,len(lists),k):
            if lists[j] < lists[j-k]:
                value = lists[j]
                lists[j] = lists[j-k]
                m = j - k
                while m >= k and lists[m-k] > value:
                    lists[m] = lists[m-k]
                    m -= k
                lists[m] = value




# x = [85, 98, 76, 54, 25, 47, 36, 4]
# ShellSort(x)








