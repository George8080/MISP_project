import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv('./TimeQuality_Results/Time_Quality_table_n2000_p0c0.1_5.graph.csv')
data.columns = data.columns.str.strip()

# print(data)

plt.figure(figsize=(10, 8))
plt.plot(data['Time'], data['Quality'], color='r')
plt.title('Resultados Calidad/Tiempo para IterativeGreedyMISP (Tamaño 2000, Densidad 0.1)')
plt.xlabel('Tiempo (ns)')
plt.ylabel('Calidad')
#plt.legend()
plt.tick_params(axis='x')
plt.tick_params(axis='y')
plt.grid(True)
plt.savefig('dataset_ItGreedyMISP_2000.png')