echo "tipoTabla;tipoDatos;sizeTabla;tipoClave;numBusquedas;tiempo"

for (( exp=1; exp<=100; exp++ ))
do
    for n in 1000 5000 10000 15000 20000
    do
    ./search_entries twitter_data closed_hash_linear username $n
    ./search_entries dummy_data closed_hash_linear username $n
    ./search_entries twitter_data closed_hash_linear user_id $n
    ./search_entries dummy_data closed_hash_linear user_id $n
    done
done