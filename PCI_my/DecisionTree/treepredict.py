# -*- coding: utf-8 -*-
my_data=[['slashdot','USA','yes',18,'None'],
        ['google','France','yes',23,'Premium'],
        ['digg','USA','yes',24,'Basic'],
        ['kiwitobes','France','yes',23,'Basic'],
        ['google','UK','no',21,'Premium'],
        ['(direct)','New Zealand','no',12,'None'],
        ['(direct)','UK','no',21,'Basic'],
        ['google','USA','no',24,'Premium'],
        ['slashdot','France','yes',19,'None'],
        ['digg','USA','no',18,'None'],
        ['google','UK','no',18,'None'],
        ['kiwitobes','UK','no',19,'None'],
        ['digg','New Zealand','yes',12,'Basic'],
        ['slashdot','UK','no',21,'None'],
        ['google','UK','yes',18,'Basic'],
        ['kiwitobes','France','yes',19,'Basic']]

class decisionnode:
    def __init__ (self, col = -1, value = None, results = None, tb = None, fb = None):
        self.col = col
        self.value = value
        self.results = results
        self.tb = tb
        self.fb = fb

def uniquecounts(rows):
    results = {}
    for row in rows:
        r = row[len(row) - 1]
        if r not in results: results[r] = 0
        results[r] += 1
    return results

def entropy(rows):
    from math import log
    log2 = lambda x:log(x)/log(2)
    ent = 0.0
    results = uniquecounts(rows)
    for r in results.keys():
        p = float(results[r])/len(rows)
        ent = ent - p * log2(p)
    return ent

def divideset(rows, column, value):
    split_function = None
    if isinstance(value, int) or isinstance(value, float):
        split_function = lambda row:row[column] >= value
    else:
        split_function = lambda row:row[column] == value

    set1 = [row for row in rows if split_function(row)]
    set2 = [row for row in rows if not split_function(row)]
    return (set1,set2)

def buildtree(rows, scoref = entropy):
    if (len(rows) == 0): return decisionnode()
    current_score = scoref(rows)

    best_gain = 0.0
    best_criteria = None
    best_sets = None
    for col in range(len(rows[0]) - 1):
        column_values = set()
        for row in rows:
            column_values.add(row[col])

        for value in column_values:
            (set1, set2) = divideset(rows, col, value)
            #信息增益
            p = len(set1)/len(rows)
            gain = current_score - p * scoref(set1) - (1-p) * scoref(set2)
            if gain > best_gain :
                if (len(set1) == 0 or len(set2) == 0):
                    print("error your way, please according to the book")
                    print(rows)
                    print(set1)
                    print(set2)
                best_gain = gain
                best_criteria = (col, value)
                best_sets = (set1, set2)

    if best_gain > 0:
        ture_branch = buildtree(best_sets[0])
        false_branch = buildtree(best_sets[1])
        return decisionnode(col = best_criteria[0], value = best_criteria[1],
                            tb = ture_branch, fb = false_branch)
    else:
        return decisionnode(results=uniquecounts(rows))

tree = buildtree(my_data)

def getwidth(tree):
  if tree.tb==None and tree.fb==None: return 1
  return getwidth(tree.tb)+getwidth(tree.fb)

def getdepth(tree):
  if tree.tb==None and tree.fb==None: return 0
  return max(getdepth(tree.tb),getdepth(tree.fb))+1


from PIL import Image,ImageDraw

def drawtree(tree,jpeg='tree.jpg'):
  w=getwidth(tree)*100
  h=getdepth(tree)*100+120

  img=Image.new('RGB',(w,h),(255,255,255))
  draw=ImageDraw.Draw(img)

  drawnode(draw,tree,w/2,20)
  img.save(jpeg,'JPEG')
  
def drawnode(draw,tree,x,y):
  if tree.results==None:
    # Get the width of each branch
    w1=getwidth(tree.fb)*100
    w2=getwidth(tree.tb)*100

    # Determine the total space required by this node
    left=x-(w1+w2)/2
    right=x+(w1+w2)/2

    # Draw the condition string
    draw.text((x-20,y-10),str(tree.col)+':'+str(tree.value),(0,0,0))

    # Draw links to the branches
    draw.line((x,y,left+w1/2,y+100),fill=(255,0,0))
    draw.line((x,y,right-w2/2,y+100),fill=(255,0,0))
    
    # Draw the branch nodes
    drawnode(draw,tree.fb,left+w1/2,y+100)
    drawnode(draw,tree.tb,right-w2/2,y+100)
  else:
    txt=' \n'.join(['%s:%d'%v for v in tree.results.items()])
    draw.text((x-20,y),txt,(0,0,0))
    
    
def classify(observation, tree):
    if tree.results != None:
        return tree.results
    else:
        v = observation[tree.col]
        branch = None
        if isinstance(v, int) or isinstance(v, float):
            if v >= tree.value :
                branch = tree.tb
            else:
                branch = tree.fb
        else:
            if v == tree.value:
                branch = tree.tb
            else:
                branch = tree.fb
        return classify(observation, branch)

classify(['(direct)', 'USA', 'yes', 5], tree)

def prune(tree, mingain):
    if tree.tb.results == None:
        prune(tree.tb)
    if tree.fb.results == None:
        prune(tree.fb)
    
    if tree.tb.results != None and tree.fb.results != None:
        tb = []
        fb = []
        for v,c in tree.tb.results.items():
            tb += [[v]] * c
        for v,c in tree.fb.results.items():
            fb += [[v]] * c
        
        delta = entropy(tb + fb) - (entropy(tb) + entropy(fb)/2)
        
        if delta < mingain :
            tree.tb, tree.fb = None, None
            tree.results = uniquecounts(tb + fb)
            
def variance(rows):
    if len(rows) == 0: return 0
    data = [float(row[len(rows[0]) - 1]) for row in rows]
    mean = sum(data)/len(data)
    variance = sum([(d - mean) ** 2 for d in data])/len(data)
    return variance
        
        