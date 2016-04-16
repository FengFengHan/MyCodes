#coding = utf-8
import ValidSort
def RadixSort(lists,radix = 10):
    maxV = max(lists)
    d = 0 # number of digit
    while True:
        d += 1
        maxV = maxV // 10
        if maxV == 0:
            break;
    # for i in range(1,d + 1):
    #     bucket = [[] for i in range(radix)]
    #     for val in lists:
    #         k = (val % (radix ** i))//(radix ** (i-1))
    #         bucket[k].append(val)
    #     del lists[:]
    #     for val in bucket:
    #         lists.extend(val)
    bucket = [[] for i in range(radix)]
    for i in range(1,d + 1):
        for val in lists:
            k = (val % (radix ** i))//(radix ** (i-1))
            bucket[k].append(val)
        del lists[:]
        for val in bucket:
            lists.extend(val)
        bucket = [[] for i in range(radix)]

# x =  [72, 13, 14, 51, 5, 41, 8, 100]
# RadixSort(x)
ValidSort.valid(RadixSort)