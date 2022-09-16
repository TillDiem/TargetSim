#!/bin/bash

#Define .C script that we want ROOT to interprete later on
ROOTScript="macro.C"

#declare -a NEUTFileArraye=("NEUTFile_XSec_cos_AllTemp_nue") # fraction
declare -a NEUTFileArray=("output0")  # raw SF_e
declare -a RunOverFile=(1 0)
InputDirectory="Input"

#Defining input and output directory with respect to current directory
#Looping over available NEUT files
for ((i=0;i<${#NEUTFileArray[@]};++i))
do
	if [ ${RunOverFile[i]} -eq 1 ]
	then
	#Getting the variables at the current iterator

	NEUTFile="${NEUTFileArray[i]}"

	echo "Currently working on: "$NEUTFile

	#Define output directories for PNGs and ROOT file
	OutputDirectory="Output"
	PNGOutputFolderName=$OutputDirectory"/PNGs/"$NEUTFile
	ROOTOutputFolderName=$OutputDirectory"/ROOT"

	#Create output directories (the -p option checks if the output directory already exists and does nothing in case they do)
	mkdir -p $PNGOutputFolderName
	mkdir -p $ROOTOutputFolderName

	root -l -b -q $ROOTScript'("'$NEUTFile'", "'$InputDirectory'", "'$OutputDirectory'")'
	fi
done

echo ""
echo "All done"
