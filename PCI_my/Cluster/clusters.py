#coding = utf-8

from PIL import Image,ImageDraw

##############################################################
#cluster
################################################
##readfile
def readfile(filename):
    lines = [line for line in file(filename)]

    colnames = lines[0].strip().split('\t')[1:] #name for column

    rownames = []
    data = []
    for line in lines[1:]:
        p = line.strip().split('\t')
        rownames.append(p[0])
        data.append([float(x) for x in p[1:]])

    return colnames,rownames,data


##closeness for two set
###cofficient of pearson
from math import  sqrt
def pearson(v1,v2):
    sum1 = sum(v1)
    sum2 = sum(v2)
    sum1sq = sum([pow(v,2) for v in v1])
    sum2sq = sum([pow(v,2) for v in v2])
    psum = sum([v1[i]*v2[i] for i in range(len(v1))])

    num = len(v1)
    Cov_1_2 = psum/num - (sum1/num)*(sum2/num)
    Std1_Std2 = sqrt((sum1sq/num - pow(sum1/num,2))*(sum2sq/num - pow(sum2/num,2)))
    if Std1_Std2 == 0:
        return 0
    return 1.0 - Cov_1_2/Std1_Std2

#class for cluster
class bicluster:
    def __init__(self,vec,left = None,right = None,distance = 0.0,id = None):
        self.left = left
        self.right = right
        self.vec = vec
        self.distance = distance
        self.id = id

#hierarchial cluster
def hcluster(rows,distance = pearson):
    distances = {}
    currentclusterid = -1
    clust = [bicluster(rows[i],id=i) for i in range(len(rows))]
    while(len(clust) > 1):
        lowestpair = (0,1)
        closet = distance(clust[0].vec,clust[1].vec)

        for i in range(len(clust)):
            for j in range(i + 1,len(clust)):
                if(clust[i].id,clust[j].id) not in distances:
                    distances[(clust[i].id,clust[j].id)] = distance(clust[i].vec,clust[j].vec)
                d =distances[(clust[i].id,clust[j].id)]
                if(d < closet):
                    lowestpair = (i,j)
                    closet = d
        mergevec = [(clust[lowestpair[0]].vec[i] + clust[lowestpair[1]].vec[i])/2.0 for i in range(len(clust[0].vec))]
        newcluster = bicluster(mergevec,left = clust[lowestpair[0]],right =clust[lowestpair[1]],distance = closet,id = currentclusterid)

        currentclusterid -= 1
        del clust[lowestpair[1]]
        del clust[lowestpair[0]]
        clust.append(newcluster)

    return clust[0]



#print the clust
def printclust(clust,labels=None,n=0):
    for i in range(n): print ' ',
    if clust.id < 0:
        print '-'
    else:
        if labels ==  None:
            print clust.id
        else:
            print labels[clust.id]

    #print left of the clust
    if clust.left != None:  printclust(clust.left,labels = labels,n = n + 1)
    #print right of the clust
    if clust.right != None: printclust(clust.right,labels = labels,n = n + 1)

#printclust(clust,labels = words)

##################################################################
#Plot the tree picture of clust

##the height of clust
def getheight(clust):
    #leaf node
    if clust.left == None and clust.right == None:
        return 1
    #branch
    return getheight(clust.left) + getheight(clust.right)

#the width of clust
def getdepth(clust):
    #leaf node
    if clust.left == None and clust.right == None:
        return 0
    return max(getdepth(clust.right),getdepth(clust.right)) + clust.distance

#plot the tree picture of clust
def drawdendrogram(clust,labels,jpeg = 'clusters.jpg'):
    #size of the picture
    hscaling = 20
    h = getheight(clust)*hscaling
    w = 1200
    depth = getdepth(clust)
    scaling = (1200 - 150)/depth
    #generate the picture
    img = Image.new('RGB',(w,h),(255,255,255))
    draw = ImageDraw.Draw(img)
    #start ploting
    draw.line((0,h/2,10,h/2),fill=(255,255,255))
    drawnode(draw,clust,0,h/2,hscaling,scaling,labels)
    img.save(jpeg,'JPEG')

#plot the node of clust
def drawnode(draw,clust,x,y,hscaling,scaling,labels):
    if clust.id < 0:
        h1 = getheight(clust.left)*hscaling
        h2 = getheight(clust.right)*hscaling
        top = y -(h1 + h2)/2
        bottom = y + (h1 + h2)/2

        #plot the vertical line
        draw.line((x,top + h1/2,x,bottom - h2/2),fill=(255,0,0))

        #line to left and right
        ll = clust.distance*scaling
        if x + ll > 2000:
            print "x + ll is: ",
            print (x + ll)
        draw.line((x,top + h1/2,x + ll,top + h1/2),fill=(255,0,0))
        draw.line((x,bottom - h2/2,x + ll,bottom - h2/2),fill=(255,0,0))

        #plot the left of clust
        drawnode(draw,clust.left,x+ll,top + h1/2,hscaling,scaling,labels)

        #plot the right of clust
        drawnode(draw,clust.right,x+ll,bottom - h2/2,hscaling,scaling,labels)
    else:
        draw.text((x+5,y-7),labels[clust.id],(0,0,0))

blognames,words,data = readfile('blogdata.txt')
clust = hcluster(data)
drawdendrogram(clust,blognames,jpeg='blogclust.jpg')