reset
set ylabel '%'
set xlabel 'NO.i test'
set term png enhanced font 'Verdana, 10'
set output '2average.png'
set title 'compare L1 cache load miss rate (random average)'
set yrange [0:0.1]
set style line 1 \
    linecolor rgb '#0060ad' \
    linetype 1 linewidth 2 \
    pointtype 7 pointsize 1.5
set style line 2 \
    linecolor rgb '#87b064' \
    linetype 1 linewidth 2 \
    pointtype 7 pointsize 1.5


plot '2average.dat' using 1:2  with lines linestyle 1 title 'index 256' ,\
'2average.dat' using 1:3 with lines linestyle 2 title 'index 65526'

