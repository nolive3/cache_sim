for rep in L N
do
	for fet in B E
	do
		for i in {0..15}
		do
			for trace in astar bzip2 mcf perlbench
			do
				./test_script $i $fet $rep $trace.trace > $trace$fet$rep$i.res
			done
		done
	done
done
