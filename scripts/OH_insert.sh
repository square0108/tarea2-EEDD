echo "tipoTabla;sizeTabla;tipoClave;numElementos;tiempo"

for (( exp=1; exp<=50; exp++ ))
do
    for n in 2500 5000 7500 10000 12500 15000 17500 20000
    do
    ./insert_entries open_hash username $n
    done
done

for (( exp=1; exp<=50; exp++ ))
do
    for n in 2500 5000 7500 10000 12500 15000 17500 20000
    do
    ./insert_entries open_hash user_id $n
    done
done