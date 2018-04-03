set terminal pngcairo size 1000, 600
set output 'comparatif.png'
set xlabel "nombre de colonnes (= nombre de lignes+1)"
set ylabel "temps (s)"
set title "Comparatif Algo naif / Algo par couleur"
set style line 10 linetype 1 \
    	       	  linewidth 3

set key on inside top left
plot "algo_couleur.temps" using 2:4 with lines title "Algo par couleur" linestyle 10, \
"algo_naif.temps" using 2:4 with lines title "Algo naif" 

