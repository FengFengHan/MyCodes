x = [49,38,65,97,76,13,27,6]

def BInsertSort(lists):
    for i in range(1,len(lists)):
        if lists[i] < lists[i-1]:
            list[i] = lists[i-1]
            value =lists[i]
            low = 0
            high = i-1
            while low < high:
                mid = (low + high)//2
                if lists[mid] <= value:
                    low = mid + 1
                else:
                    high = mid - 1
            for j in range(low,i-1):
                lists[j + 1] = lists[j]
            list[low] = value


