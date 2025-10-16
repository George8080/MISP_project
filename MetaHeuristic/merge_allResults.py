import pandas as pd

# Load the two CSV files
df1 = pd.read_csv('./results_MISP_avg.csv')  # Replace with your file path
df2 = pd.read_csv('./results_ItGreedyMISP_avg.csv')  # Replace with your file path

# Merge the two dataframes on 'Size' and 'Density'
merged_df = pd.merge(df1, df2, on=['Size', 'Density'], how='outer')

# Save the merged dataframe to a new CSV file
merged_df.to_csv('allMISP_results_act2.csv', index=False)

print("Merged CSV has been saved as 'allMISP_results_act2.csv'")
