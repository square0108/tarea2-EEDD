echo "tipoTabla;dataSet;sizeTabla;tipoClave;numElementos;tiempo"

for (( exp=1; exp<=50; exp++ ))
do
    for n in 2500 5000 7500 10000 12500 15000 17500 20000
    do
    ./search_entries twitter_data closed_hash_linear username $n
    ./search_entries twitter_data closed_hash_double username $n
    ./search_entries twitter_data closed_hash_quadratic username $n
    ./search_entries twitter_data open_hash username $n
    ./search_entries twitter_data STL_map username $n
    done
done