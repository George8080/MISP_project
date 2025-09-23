import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv('results_MISP_avg.csv')
data = data[data.Size == 2000]
data.columns = data.columns.str.strip()

# print(data)

plt.figure(figsize=(10, 8))
plt.plot(data['Density'], data['Greedy_Value'], color='r', label='Valores medio usando Greedy')
plt.plot(data['Density'], data['GreedyRan_Value'], color='b', label='Valores medio usando RandomGreedy')
plt.title('Resultados de valores entre MISP_Greedy y MISP_RandomGreedy (Tamaño 2000)')
plt.xlabel('Densidad')
plt.ylabel('Tiempo (ns)')
plt.legend()
plt.tick_params(axis='x')
plt.tick_params(axis='y')
plt.grid(True)
plt.savefig('dataset_grafos_no_dirigidos_2000_Value.png')