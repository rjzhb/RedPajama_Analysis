# Set the terminal to PNG and output file
set terminal png
set output 'cws.png'

# Set style for histogram
set style data histogram
set style histogram cluster gap 1
set style fill pattern

# Change the location of the legend
set key left top
set xrange [-0.5:3.5]

# Set the xtics to display your categories
set xtics ("1M" 1, "2M" 2, "4M" 3, "8M" 4)

# Plot the data
plot 'cws_amounts.txt' using 2:xtic(1) title 't=25' lt rgb "purple" fs pattern 1, '' using 3 title 't=50' lt rgb "forest-green" fs pattern 2, '' using 4 title 't=100' lt rgb "medium-blue" fs pattern 37
