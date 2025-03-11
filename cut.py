with open('C:\Users\1234\Desktop\jsdata.csv', newline='') as csvfile:

  # 以冒號分隔欄位，讀取檔案內容
  rows = csv.reader(csvfile, delimiter=',')

  for row in rows:
    print(row)
