import pandas as pd
import csv
df = pd.read_csv("jsdata.txt",delimiter="\t")
df.to_csv("jsdata.csv", encoding='utf-8', index=False)

with open('C:\\Users\1234\Desktop\jsdata.csv', newline='') as csvfile:

  # 以冒號分隔欄位，讀取檔案內容
  rows = csv.reader(csvfile, delimiter=',')

  for row in rows:
    print(row)
