
#!/usr/bin/env bash
set -euo pipefail

OUT="results_MISP.csv"
GREEDY="./greedyMISP.exe" 
GREEDY_RAN="./greedyRandomMISP.exe"
DATASET_ROOT="./dataset_grafos_no_dirigidos"
echo "Size,Density,Number,Greedy_Value,Greedy_Time,GreedyRan_Value,GreedyRan_Time" > "$OUT"

for X in 1000 2000 3000; do
  for Y in 0.{1..9}; do
    for Z in {1..30}; do
      FILE=./dataset_grafos_no_dirigidos/new_"$X"_dataset/erdos_n"$X"_p0c"$Y"_"$Z".graph
      IFS=, read -r G1 G2 < <(./greedyMISP.exe -i "$FILE")
      IFS=, read -r R1 R2 < <(./greedyRandomMISP.exe -i "$FILE" 50 5)
      echo "$X,$Y,$Z,$G1,$G2,$R1,$R2" >> "$OUT"
    done
  done
done
