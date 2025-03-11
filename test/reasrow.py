import csv
import nltk

f = open("data.csv","r")
readerf = csv.reader(f)
temp = []
for row in readerf:
    temp.append(postag(row)[1])

from collections import Counter
Counter(temp)
