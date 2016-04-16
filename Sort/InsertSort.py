def InsertSort(lists):
    for i in range(1,len(lists)):
        value = lists[i]
        j = i - 1
        while j >= 0 and lists[j] > value:
            lists[j+1] = lists[j]
            j -= 1
        lists[j+1] = value


