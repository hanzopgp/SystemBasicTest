#/bin/bash

clear 
gcc client_reseau.c -o client_reseau
gcc  serveur_reseau_parallele.c -o  serveur_reseau_parallele
killall serveur_reseau_parallele
#netstat -npt | grep 50000 
./serveur_reseau_parallele &
#netstat -t | grep 50000 
#On lance les 6 clients qui attendent 3 secondes apres connexion
./client_reseau &
./client_reseau & 
./client_reseau & 
./client_reseau & 
./client_reseau & 
./client_reseau &
ps -jH
netstat -npt | grep 50000 
echo "Fini, au boulot on explique le resultat... ;-)"

