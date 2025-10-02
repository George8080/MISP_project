import pandas as pd

file_path = './results_MISP.csv'
df = pd.read_csv(file_path)

df_grouped = df.drop(columns='Number').groupby(['Size', 'Density']).mean().reset_index()
df_grouped.to_csv('results_MISP_avg.csv', index=False)
