x = [49,38,65,97,76,13,27,6]

def QuickSort(lists):
    QSort(lists,0,len(lists)-1)

def QSort(lists,start,end):
    if start >= end:
        return
    keyLoc = Partion(lists,start,end)
    QSort(lists,start,keyLoc)
    QSort(lists,keyLoc + 1,end)

def Partion(lists,low,high):
    key = lists[low]
    while low < high:
        while high > low and lists[high] >= key:
            high -= 1
        lists[low] = lists[high]
        while low < high and lists[low] < key:
            low += 1
        lists[high] = lists[low]
    lists[low] = key
    return low
