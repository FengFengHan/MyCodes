# -*- coding: utf-8 -*-
"""
Created on Mon Sep 07 15:30:40 2015

@author: Administrator
"""

import time
import random
import math

'''
util
'''
def getminutes(t):
    x= time.strptime(t, '%H:%M')
    return x[3] * 60 + x[4]

'''
people
'''
people = [('Seymour', 'BOS'),
          ('Franny', 'DAL'),
          ('Zooey', 'CAK'),
           ('Walt', 'MIA'),
('Buddy', 'ORD'),
('Les', 'OMA')]

destination = 'LGA'

'''
flight
'''
flights = {}
f = open('schedule.txt')
for line in f:
    origin, dest, depart, arrive, price = line.strip().split(',')
    flights.setdefault((origin, dest), [])
    flights[(origin, dest)].append((depart, arrive, int(price)))

# schedule
def printschedule(r):
    for d in range(len(r)//2):
        name = people[d][0]
        origin = people[d][1]
        out = flights[(origin, destination)][r[2*d]]
        ret = flights[(destination, origin)][r[2*d + 1]]
        print('%10s%10s %5s-%5s %3s %5s-%5s %3s' %(name, origin, 
                                                     out[0], out[1], out[2],ret[0], ret[1], ret[2]))
    


def schedulecost(sol):
    
    totalprice = 0;
    latestarrival = 0;
    earliestdep = 24 * 60;
    for d in range(len(sol)//2):
        origin = people[d][1]
        outbound = flights[(origin, destination)][sol[2*d]]
        returnf = flights[(destination, origin)][sol[2*d + 1]]
        totalprice += outbound[2]
        totalprice += returnf[2]
        if latestarrival < getminutes(outbound[1]):
            latestarrival = getminutes(outbound[1])
        if earliestdep > getminutes(returnf[0]):
            earliestdep = getminutes(returnf[0])
    
    totalwait = 0
    for d in range(len(sol)//2):
        origin = people[d][1]
        outbound = flights[(origin, destination)][sol[2*d]]
        returnf = flights[(destination, origin)][sol[2*d + 1]]
        totalwait += latestarrival - getminutes(outbound[1])
        totalwait += getminutes(returnf[0]) - earliestdep
    
    # Does this solution require an extra day of car rental? That'll be $50!
    if latestarrival>earliestdep: 
        totalprice+=50
    
    return totalprice + totalwait
    
def randomoptimization(domain, costf):
    best = 999999999
    bestr = None
    for j in range(1000):
        r = [random.randint(domain[i][0], domain[i][1]) for i in range(len(domain))]
        cost = costf(r)
        if cost < best:
            best = cost
            bestr = r
    return bestr

def hillclimb(domain, costf):
    #create a random  solution
    sol = [random.randint(domain[i][0], domain[i][1]) for i in range(len(domain))]
    
    #main loop
    while True:
        #create neighbor
        neighbors = []
        for j in range(len(domain)):
            if sol[j] > domain[j][0]:
                neighbors.append(sol[0:j] + [sol[j] - 1] + sol[j + 1:])
            if sol[j] < domain[j][1]:
                neighbors.append(sol[0:j] + [sol[j] + 1] + sol[j+1:])
    
        #find best sol in neighbor
        currentf = costf(sol)
        best = currentf
        for neighbor in neighbors:
            cost = costf(neighbor)
            if cost < best:
                best = cost
                sol = neighbor
        
        #if best == current, then end
        if best == currentf:
            break
    
    return sol

def annealingoptimize(domain, costf, T= 10000.0, cool = 0.95, step = 1):
    #create a random solution
    sol = [random.randint(domain[i][0], domain[i][1]) for i in range(len(domain))]
    
    #annealing
    while T > 0.1:
        #select a index
        i = random.randint(0, len(domain) - 1)
        #change the index
        dir = random.randint(-step, step)
        neighbor= sol[:]
        neighbor[i] += dir
        if neighbor[i] < domain[i][0]:
            neighbor[i] = domain[i][0]
        elif neighbor[i] > domain[i][1]:
            neighbor[i] = domain[i][1]
        ea = costf(sol)
        eb = costf(neighbor)
        if (eb < ea or random.random() < pow(math.e, -(eb - ea)/T)):
            sol = neighbor
        
        T = T * cool
    return sol
        
#### the bug has not been solved
def geneticoptimize(domain, costf, popsize = 50, step = 1, 
                    mutprob = 0.2, elite = 0.2, maxiter = 100):
    # mut operation
    def mutate(vec):
        i = random.randint(0, len(domain) - 1)
        if random.random() < 0.5 and vec[i] > domain[i][0]:
            return vec[0:i] + [vec[i] - 1] + vec[i + 1:]
        elif vec[i] < domain[i][1]:
            return vec[0:i] + [vec[i] + 1] + vec[i + 1:]

    #cross operation
    def cross(r1, r2):
        i = random.randint(1,len(domain)-2)
        return r1[:i] + r2[i:]

    #create a population
    pop = []
    for i in range(popsize):
        vec = [random.randint(domain[i][0], domain[i][1]) for i in range(len(domain))]
        pop.append(vec)

    #elite number
    topelite = int(popsize * elite);

    for i in range(maxiter):
        #select elite
        scores = [(costf(v),v) for v in pop]
        scores.sort()
        ranked = [v for (s,v) in scores]
        pop = ranked[0:topelite]
        #mut or cross
        while len(pop) < popsize:
            if random.random() < mutprob:
                c = random.randint(0, topelite)
                pop.append(mutate(ranked[c]))
            else:
                c1 = random.randint(0, topelite)
                c2 = random.randint(0, topelite)
                pop.append(cross(ranked[c1], ranked[c2]))

        print(scores[0][0])

    return scores[0][1]




