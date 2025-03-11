import pandas as pd
df = pd.read_csv("tocsv.txt",delimiter="\t")
df.to_csv("tocsv.csv", encoding='utf-8', index=False)
