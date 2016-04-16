#!/usr/bin/env python
#coding:utf-8

import json
from urllib import request
import sys
import  imp
imp.reload(sys)                      #要reload一次sys才能使用setdefaultencoding函数
import re
#sys.setdefaultencoding('utf-8')  #要将系统默认字符编码设置为utf-8,在Goldendict才能正常输出

html = """
<html>
<head>
<meta charset="UTF-8">
<script type="text/javascript">function playSound(){var ky = document.getElementById("key");var word = ky.childNodes[0].nodeValue;var api = "http://dict.youdao.com/dictvoice?audio=" + encodeURIComponent(word);var ado = document.getElementById("media");try{ado.ended = true;ado.setAttribute("src",api);ado.load();ado.play();return false;}catch(err){alert(err.description);return false;}}</script>
</head>
<body>
<style type="text/css">
      div.block {
      border:1px solid #BEBEBE;
      background:#F0F0F0;
      margin-left:20px;
      border-radius: 5px;
      }
      div.name {
      margin-top:10px;
      margin-bottom:5px;
      margin-left:20px;
      font-size:13px;
      font-weight:bold;
      }
      div.item {
      padding:5px;
      font-size:12px;
      margin: 0px 10px 0px 10px;
      }
      #web {
      border-style: none none solid none;
      border-color: #BEBEBE;
      border-bottom-width: 1px;
      }
    </style>
    <div class="content">
      %s
    </div>
</body>
</html>
"""

errorHtml = """
<html><body>
<div class="block">
<div class="item">%</div>
</div>
</body></html>
"""

errorResult = {'0':'', '20':'要翻译的文本过长', '30':'无法进行有效的翻译',
              '40':'不支持的语言类型', '50':'无效的key'}

def data2Html(errorCode, query, basic):
    """打印html"""
    if errorCode != 0:
        print(errorHtml % errorResult[errorCode])
        return
    item = '<div class="item">%s</div>'
    q = item % ('<b>"%s"</b>' % query)
    key = ''
    if basic:
        key += '<span id="key" style="font-weight:bold">%s</span>' % (query + ' ')
        if 'us-phonetic' in basic.keys():
            key += '[%s]' % basic['us-phonetic']
            key += '<button id="sound" onclick="playSound()">sound</button><audio id="media"></audio>'
        key = item % key
    if not key:
        key = item % '对不起,没有结果'
    key = '<div class= "block">\n' + key + '</div>'
    return key

def getData(word):
    url = r'http://fanyi.youdao.com/openapi.do?keyfrom=hanhuifengblog&key=1723548065&type=data&doctype=json&version=1.1&q=' + word
    f = request.urlopen(url)
    jsonStr = str(f.read(),encoding = "utf-8")
    data = json.loads(jsonStr)
    # errorCode = data['errorCode']
    # query = data['query']
    # translation = data['translation']
    # basic = {}
    # if 'basic' in data.keys():
    #     basic = data['basic']
    # web = []
    # if 'web' in data.keys():
    #     web = data['web']
    return data

def getQueryResult(word):
    data = getData(word)
    basic = {}
    if 'basic' in data.keys():
        basic = data['basic']
    result = data2Html(data['errorCode'], data['query'], basic)
    return  result

# if __name__ == '__main__':
#     searchWord(sys.argv[1])
def getWords(fileName):
    f = open(fileName)
    content = f.read()
    words = re.split(r'[^(A-Za-z)]\s*',content)
    return words
#path = "/Users/HAN/Documents/"
path = ""
file = "Lesson92"
words = getWords(path + file + ".txt")
wordsHtml = ""
for word in words:
    if word != None and len(word) > 0:
        word = word.lower()
        print(word)
        wordsHtml = wordsHtml + getQueryResult(word) + "\n"
result = (html % wordsHtml)
f = open(file + ".html",'w')
f.write(result)
f.close()



