import ValidSort
def CountingSort(lists):
    count = [0] * (max(lists) + 1)
    for i in range(len(lists)):
        count[lists[i]] += 1
    for j in range(1,len(count)):
        count[j] += count[j-1]
    res = [0] * (len(lists) + 1)
    for i in range(len(lists)-1,-1,-1):
        count[lists[i]] -= 1
        res[count[lists[i]]] = lists[i]
    # for j in range(len(lists)):
    #     lists[j] = res[j]
    return res
    # index = 0
    # for m in range(len(count)):
    #     while(count[m] > 0):
    #         lists[index] = m
    #         index += 1
    #         count[m] -= 1
ValidSort.valid(CountingSort)
