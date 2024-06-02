echo "tipoTabla;sizeTabla;tipoClave;numElementos;tiempo"

for (( exp=1; exp<=200; exp++ ))
do
    for n in 1000 5000 10000 15000 20000
    do
    ./insert_entries closed_hash_linear user_id $n
    done
done