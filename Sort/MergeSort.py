import  ValidSort
def Merge(lists,s1,e1,s2,e2):
    tmp = []
    cur1, cur2 = s1, s2
    while cur1 < e1 and cur2 < e2:
        if lists[cur1] <= lists[cur2]:
            tmp.append(lists[cur1])
            cur1 += 1
        else:
            tmp.append(lists[cur2])
            cur2 += 1
    cur ,e = (cur1,e1) if cur1 < e1 else (cur2,e2)
    while cur < e:
        tmp.append(lists[cur])
        cur += 1
    for i in range(len(tmp)):
        if s1 < e1:
            lists[s1] = tmp[i]
            s1 += 1
        else:
            lists[s2] = tmp[i]
            s2 += 1

def MSort(lists,start,end):
    if end - start < 2:
        return
    mid = (start + end) //2
    MSort(lists,start,mid)
    MSort(lists,mid,end)
    Merge(lists,start,mid,mid,end)

def MergeSort(lists):
    MSort(lists,0,len(lists))

#x = [4,3,0,8,5,0]
#MergeSort(x)
ValidSort.valid(MergeSort)

