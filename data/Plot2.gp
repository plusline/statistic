reset                                                                           
set xlabel 'numerical distribution'
set ylabel 'time(cycles)'
set title 'look up table perfomance comparison'
set term png enhanced font 'Verdana,10'
set output 'beautiful.png'
set format x "%10.0f"

plot 'distribution.dat' using 1:2 with points title '256',\
'distribution.dat' using 1:3 with points title '65526'
