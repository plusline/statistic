reset                                                                           
set xlabel 'numerical distribution'
set ylabel 'time(cycles)'
set title 'perfomance comparison'
set term png enhanced font 'Verdana,10'
set output 'beautiful.png'
set format x "%10.0f"

# plot [:][:]'data1.txt' using 1:2 with points title 'non inline',\
# 'data2.txt' using 1:2 with points title 'inline',\
##
plot [:][:]'data3.txt' using 1:2 with points title 'solution2',\
'data4.txt' using 1:2 with points title 'macro+one by one',\
'data5.txt' using 1:2 with points title 'look up table 8',\
'data6.txt' using 1:2 with points title 'look up table 16'
