for rep in L N
do
	for fet in B E
	do
		for i in {0..15}
		do
			for trace in astar bzip2 mcf perlbench
			do
				octave plot.m $trace $i $fet $rep
			done
		done
	done
done
