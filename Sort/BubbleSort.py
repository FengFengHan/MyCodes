x = [49,38,65,97,76,13,27,49]

def BubbleSort(lists):
    count = len(lists)
    for i in range(count):
        order = True
        for j in range(0,count-1-i):
            if lists[j] > lists[j+1]:
                order = False
                lists[j], lists[j+1] = lists[j+1],lists[j] #swap
        if order:
            return



