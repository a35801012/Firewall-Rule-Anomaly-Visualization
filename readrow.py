with open('jsdata.csv','rb') as csvfile:
    reader = csv.reader(csvfile)
    column = [row[2] for row in reader]
