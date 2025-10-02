import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv('results_MISP_avg.csv')
data = data[data.Size == 3000]
data.columns = data.columns.str.strip()

# print(data)

plt.figure(figsize=(10, 8))
plt.plot(data['Density'], data['Greedy_Time'], color='r', label='Tiempo medio usando Greedy')
plt.plot(data['Density'], data['GreedyRan_Time'], color='b', label='Tiempo medio usando RandomGreedy')
plt.title('Resultados de tiempo entre MISP_Greedy y MISP_RandomGreedy (Tamaño 3000)')
plt.xlabel('Densidad')
plt.ylabel('Tiempo (ns)')
plt.legend()
plt.tick_params(axis='x')
plt.tick_params(axis='y')
plt.grid(True)
plt.savefig('dataset_grafos_no_dirigidos_3000_Time.png')