#!/bin/bash

menu_choice=""
current_cd=""
tracks_file="tracks.cdb"
title_file="title.cdb"
temp_file=/tmp/cdb.$$
trap 'rm -f $temp_file' EXIT

get_return()
{
	echo -e "press return\c"
	read x
	return 0
}
get_confirm()
{
	echo -e "are you sure \c"
	while true
	do
		read x
		case "$x" in
			y|Y)
				return 0;;
			n|N)
				echo
				echo "cancell"
				return -1;;
			*) 
				echo "please enter y or n";
		esac
	done
}
set_menu_choice()
{
	clear	
	echo -e "now,the selected cd is $cdcatnum,cd title is $cdtitle"
	echo "options :-"
	echo
	echo -e "\ta)add new cd"
	echo -e "\tf)find cd"
	echo -e "\tc)count the cds and tracks in the catalog"
	if [ "$cdcatnum" != "" ]; then
		echo -e "\t\tl)list tracks on $cdtitle"
		echo -e "\t\tr)remove $cdtitle"
		echo -e "\t\tu)update track information for $cdtitle"
	fi
	echo -e "\tq)quit"
	echo
	echo -e "please enter choice then press return \c"
	read menu_choice
	echo "YOU INPUT $menu_choice"
	return
}
insert_title()
{
	echo $* >> $title_file
	return
}
insert_track()
{
	echo $* >> $tracks_file
	return
}
add_record_tracks()
{
	echo "enter track information for this cd"
	echo "when no more tracks enter q"
	cdtrack=1
	cdtitle=""
	while [ "$cdtitle" != "q" ]
	do
		echo -e "please enter track title,track $cdtrack? \c"
		read tmp
		cdtitle=${tmp%%,*}

		if [ "$tmp" != "$cdtitle" ]; then
			echo "sorry no commas allowed"
			continue
		fi
		if [ -n "$cdtitle" ]; then
			if [ "$cdtitle" != "q" ]; then
				insert_track $cdcatnum,$cdtrack,$cdtitle
			fi
		else
			cdtrack=$((cdtrack-1))
		fi
		cdtrack=$((cdtrack+1))
	done
}
add_records()
{
	echo -e "enter catalog name: \c"
	read tmp
	cdcatnum=${tmp%%,*}

	echo -e "enter title: \c"
	read tmp
	cdtitle=${tmp%%,*}

	echo -e "enter type: \c"
	read tmp
	cdtype=${tmp%%,*}

	echo -e "enter artist/composer: \c"
	read tmp
	cdac=${tmp%%,*}

	echo About to add new entry
	echo "$cdcatnum $cdtitle $cdtype $cdac"

	if get_confirm ; then
		insert_title $cdcatnum,$cdtitle,$cdtype,$cdac
		add_record_tracks
	else
		remove_records
	fi

	return
}
list_tracks()
{
	echo "CDCATNUM IS $cdcatnum"
	if [ "$cdcatnum" = "" ]; then
		echo no cd selected yet
		return
	else
		echo  GREP $tracks_file
		grep "^${cdcatnum}," $tracks_file > $temp_file
		num_tracks=$(wc -l $temp_file)
		if [ "$num_tracks" = "0" ]; then
			echo no tracks found for $cdtitle
		else
		{
			echo 
			echo "$cdtitle :-"
			echo
			cut -f 2- -d , $temp_file
			echo
		} | ${PAGER:-more}
		fi
	fi
	get_return
	return
}
find_cd()
{
	if [ "$1" = "n" ]; then
		asklist=n
	else
		asklist=y
	fi

	cdcatnum=""
	echo -e "enter a string to search for in the cd titles \c"
	read searchstr
	if [ "$searchstr" = "" ]; then
		return 0
	fi
	echo read-searchstr
	grep "$searchstr" $title_file > $temp_file
	echo grep
	set $(wc -l $temp_file)
	echo set
	linesfound=$1
	case "$linesfound" in
		0)
			echo "sorry,nothing found"
			get_return
			return 0;;
		1) ;;
		2)
			echo "sorry,not unique"
			echo "found the following"
			cat $temp_file
			get_return
			return 0;;
		*)	echo bigger than 2 items is found
			get_return
			return 0;;
	esac
	
	IFS=","
	read cdcatnum cdtitle cdtype cdac < $temp_file
	IFS=" "
	if [ -z "$cdcatnum" ]; then
		echo "sorry, could not extract catalog field from $temp_file"
		get_return
		return 0
	fi

	echo 
	echo catalog number:$cdcatnum
	echo title:$cdtitle
	echo type:$cdtype
	echo artist/composer:$cdac
	echo
	get_return

	if [ "$asklist" = "y" ]; then
		echo -e "view tracks for this cd? \c"
		read x
		if [ "$x" = "y" ]; then
			echo list tracks
			list_tracks
			echo
		else
			echo YOU CHOOSE NOT TO LIST TRACKS
		fi
	fi
	return 1
}

update_cd()
{
	if [ -z "$cdcatnum" ]; then
		echo "you must select a cd first"
		find_cd n
	fi
	if [ -n "$cdcatnum" ]; then
		echo "current tracks are:-"
		list_tracks
		echo "this will re-enter the tracks for $cdtitle"
		get_confirm && {
			grep -v "^${cdcatnum}," $tracks_file > $temp_file
			mv $temp_file $tracks_file
			echo
			add_record_tracks
		}
	fi
	return
}
count_cds()
{
	set $(wc -l $title_file)
	num_title=$1
	set $(wc -l $tracks_file)
	num_tracks=$1
	echo found $num_title cds,with a total of $num_tracks tracks
	get_return
	return
}
remove_records()
{
	if [ -z "$cdcatnum" ]; then
		echo you must select a cd first
		find_cd n
	fi
	if [ -n "$cdcatnum" ]; then
		echo "you are about to delete $cdcatnum"
		get_confirm && {
			grep -v "^${cdcatnum}," $title_file > $temp_file
			mv $temp_file $title_file
			grep -v "^${cdcatnumh}" $tracks_file > $temp_file
			mv $temp_file $tracks_file
			cdcatnum=""
			echo entry removed
		}
		get_return
	fi
	return
}


rm -f $temp_file
if [ ! -f $title_file ]; then
	touch $title_file
fi	
if [ ! -f $tracks_file ]; then
	touch $tracks_file
fi
clear
echo 
echo
echo "mini cd manager"
echo "SLEEP 0.3S"
sleep 0.3

quit=n
while [ "$quit" != "y" ]
do
	set_menu_choice
	case "$menu_choice" in
		a)	add_records;;

		r)	remove_records;;
		b)	echo
			more $title_file
			echo
			get_return;;
		f)	find_cd y;;
		l)	list_tracks;;
		u)	update_cd;;
		c)	count_cds;;
		q|Q)
			quit=y;;
		*)	echo "sorry,choice nor recognized";;
	esac
done

rm -f $temp_file
echo "finished,sleep 0.5s"
sleep 0.5
exit 0
