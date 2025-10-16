
#!/usr/bin/env bash
set -euo pipefail

OUT="results_ItGreedyMISP.csv"
ITERATIVE_GREEDY="./IteratedGreedyMISP.exe"
DATASET_ROOT="./dataset_grafos_no_dirigidos"
echo "Size,Density,Number,IterativeGreedy_Value,IterativeGreedy_Time" > "$OUT"

for X in 1000 2000 3000; do
  for Y in 0.{1..9}; do
    for Z in {1..30}; do
      FILE=./dataset_grafos_no_dirigidos/new_"$X"_dataset/erdos_n"$X"_p0c"$Y"_"$Z".graph
      IFS=, read -r R1 R2 < <(./IteratedGreedyMISP.exe -i "$FILE" -t 10 40 10)
      echo "$X,$Y,$Z,$R1,$R2" >> "$OUT"
    done
  done
done
