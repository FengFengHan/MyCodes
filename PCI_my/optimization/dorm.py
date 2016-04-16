import random
import math
import optimization
# The dorms, each of which has two available spaces
dorms=['Zeus','Athena','Hercules','Bacchus','Pluto']

# People, along with their first and second choices
prefs=[('Toby', ('Bacchus', 'Hercules')),
       ('Steve', ('Zeus', 'Pluto')),
       ('Karen', ('Athena', 'Zeus')),
       ('Sarah', ('Zeus', 'Pluto')),
       ('Dave', ('Athena', 'Bacchus')),
       ('Jeff', ('Hercules', 'Pluto')),
       ('Fred', ('Pluto', 'Athena')),
       ('Suzie', ('Bacchus', 'Hercules')),
       ('Laura', ('Bacchus', 'Hercules')),
       ('James', ('Hercules', 'Athena'))]
domain = [(0, len(dorms)*2 - i - 1) for i in range(len(dorms) * 2)]

def printsolution(vec):
    slots = []
    for i in range(len(dorms)): slots += [i,i]
    for i in range(len(vec)):
        x = slots[int(vec[i])]
        dorm = dorms[x]
        print(prefs[i][0], dorm)
        del slots[int(vec[i])]

def dormcost(vec):
    cost = 0
    slots = []
    for i in range(len(dorms)): slots += [i,i]
    for i in range(len(vec)):
        x = vec[i]
        dorm = dorms[slots[x]]
        if dorm == prefs[i][0]:
            pass
        elif dorm == prefs[i][1]:
            cost += 1
        else:
            cost += 3
        del slots[x]
    return cost

optimization.randomoptimization(domain, dormcost)


