#!/bin/bash

insert_track()
{
	echo $1
	echo $2
	echo $3
}
expression()
{
	while [ "$cdtitle" != "q" ]
	do
		echo -e "track $cdtrack,track title? \c"
		read tmp
		cdtitle=${tmp%%,*}

		echo cdtitle-begin
		echo $cdtitle
		echo cdtitle-end

		if [ "$tmp" != "$cdtitle" ];then
			echo "sorry no commas allowed"
			continue
		fi

		if [ -n "$cdtitle" ];then
			if [ "$cdtitle" != "q" ];then
				insert_track $cdcatnum,$cdtrack,$cdtitle
			fi
		else
			cdtrack=$((cdtrack-1))
		fi
		cdtrack=$((cdtrack+1))
	done
}
expression;
