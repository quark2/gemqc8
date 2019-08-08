#!/bin/bash

# copyNAS2EOS_raw.sh
#
# Created by: Kalpanie Madara Liyanage
#
# Usage: Copy QC8 uFEDKit run files from NAS to EOS

RUN=$(printf "%06d" $1)
DIRECTORY=/eos/cms/store/group/dpg_gem/comm_gem/QC8_Commissioning/run$RUN
src=/data/bigdisk/GEM-Data-Taking/GE11_QC8/Cosmics/run$RUN/run$RUN
COUNT=0
COPY=0

if [ ! -d "$DIRECTORY" ]; then
	echo "Creating Directory: "$DIRECTORY
	mkdir $DIRECTORY
else
	echo "Existing Directory: "$DIRECTORY
fi

#Get the list of files to send
FILES=$(ssh gemuser@gem904qc8daq ls ${src}"_ls"*".raw")

#Tell the user which group of files will be copied
echo "The list of files to be copied is:"
for f in $FILES\;
do
	echo $f
	((COUNT++))
done

MODTIME=$(ssh gemuser@gem904qc8daq date -r ${src}"_ls0001_index000000.raw" +"%Y-%m-%d_%H-%M-%S")

#Copy the files
echo "Copying files"
for f in $FILES;
do
	echo "Processing " $f
	ls=$(echo "$f" | cut -d'_' -f 3)
	index=$(echo "$f" | cut -d'_' -f 4)
	name=run$RUN"_Cosmic_CERNQC8_"$MODTIME"_"$ls"_"$index
	echo $name
	scp "gemuser@gem904qc8daq:$f" $DIRECTORY/$name
done

#Confirm for the user that the files were copied
echo "Showing the contents of " $DIRECTORY
ls -1 | wc -l $DIRECTORY"/"*".raw"
COPIED=$(ls $DIRECTORY)

for c in $COPIED;
do
	((COPY++))
done

if [ $COUNT -eq $COPY ]; then
        echo "All files have been copied!"
else
	echo "Some files are missing!"
fi
