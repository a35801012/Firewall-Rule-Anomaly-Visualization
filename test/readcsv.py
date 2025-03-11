import csv
import pandas as pd


with open('321.csv','r') as csvfile:

    reader = csv.reader(csvfile)
    column = [row[5] for row in reader]
    
print(column)
