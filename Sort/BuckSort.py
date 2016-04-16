import ValidSort

def BuckSort(A):
    n = len(A)
    bucket = [[] for j in range(n)]
    #allocate
    for i in range(n):
        bucket[int(n * A[i])].append(A[i])
    #sort in the bucket
    for j in range(n):
        if len(bucket[j]) > 0:
            InsertSort(bucket[j])
    #concatenate
    i = 0
    del A[:]
    for values in bucket:
        A.extend(values)


def InsertSort(lists):
    for i in range(1,len(lists)):
        value = lists[i]
        j = i - 1
        while j >= 0 and lists[j] > value:
            lists[j+1] = lists[j]
            j -= 1
        lists[j+1] = value

ValidSort.valid(BuckSort)