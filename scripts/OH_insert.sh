echo "tipoClave;numElementos;tiempo"

for (( exp=1; exp<=200; exp++ ))
do
    for n in 1000 5000 10000 15000 20000
    do
    ./insert_entries open_hash username $n
    done
done

for (( exp=1; exp<=200; exp++ ))
do
    for n in 1000 5000 10000 15000 20000
    do
    ./insert_entries open_hash user_id $n
    done
done