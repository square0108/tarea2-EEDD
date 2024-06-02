echo "tipoTabla;dataSet;sizeTabla;tipoClave;numElementos;tiempo"

for (( exp=1; exp<=50; exp++ ))
do
    for n in 2500 5000 7500 10000 12500 15000 17500 20000
    do
    ./search_entries twitter_data closed_hash_linear user_id $n
    ./search_entries twitter_data closed_hash_double user_id $n
    ./search_entries twitter_data closed_hash_quadratic user_id $n
    ./search_entries twitter_data open_hash user_id $n
    ./search_entries twitter_data STL_map user_id $n
    done
done