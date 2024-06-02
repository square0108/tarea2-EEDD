echo "Beginning full experiment set... "

# rm csv_results/dumSearch_usr.csv
# rm csv_results/dumSearch_id_.csv
rm csv_results/twitSearch_id.csv
rm csv_results/twitSearch_usr.csv
rm csv_results/Insert_usr.csv
rm csv_results/Insert_id.csv

# (scripts/dummy_searches_string.sh >> csv_results/dumSearch_usr.csv) && 
# (scripts/dummy_searches_id.sh >> csv_results/dumSearch_id_.csv) && 
(scripts/twitter_searches_id.sh >> csv_results/twitSearch_id.csv) && 
(scripts/twitter_searches_string.sh >> csv_results/twitSearch_usr.csv) && 
(scripts/string_insertions.sh >> csv_results/Insert_usr.csv) && 
(scripts/id_insertions.sh >> csv_results/Insert_id.csv)

echo "Experiments complete"