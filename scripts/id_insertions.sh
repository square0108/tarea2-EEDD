echo "tipoTabla;sizeTabla;tipoClave;numElementos;tiempo"

for (( exp=1; exp<=50; exp++ ))
do
    for n in 2500 5000 7500 10000 12500 15000 17500 20000
    do
    ./insert_entries closed_hash_linear user_id $n
    ./insert_entries closed_hash_double user_id $n
    ./insert_entries closed_hash_quadratic user_id $n
    ./insert_entries open_hash user_id $n
    ./insert_entries STL_map user_id $n
    done
done