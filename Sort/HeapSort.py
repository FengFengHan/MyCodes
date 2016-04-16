import ValidSort
def HeapAdjust(lists, pos, end):
    value = lists[pos]
    cur = pos
    while cur < end//2:
        left = 2 * cur + 1
        next_ = left
        right = left +1
        if right < end and lists[right] > lists[next_]:
            next_ = right
        if lists[next_] <= value:
            break
        else:
            lists[cur] = lists[next_]
        cur = next_
    lists[cur] = value

def HeapSort(lists):
    for i in range(len(lists)//2-1,-1,-1):
        HeapAdjust(lists,i,len(lists))
    for i in range(len(lists) -1,0,-1):
        lists[0],lists[i] = lists[i],lists[0]
        HeapAdjust(lists,0,i)

