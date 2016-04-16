import ValidSort
def SelectSort(lists):
    n = len(lists)
    for i in range(n):
        minIndex = i
        for j in range(i+1,n):
            if lists[j] < lists[minIndex]:
                minIndex = j
        lists[i],lists[minIndex] = lists[minIndex],lists[i]
ValidSort.valid(SelectSort)

