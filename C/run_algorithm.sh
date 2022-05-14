# !/bin/bash
# Author: Group 5
# Date Created: 4/26/2022
# Runs the algorithm on all confocal tif images in a dataset (same folder) & writes results to their own files

# use makefile to compile all required files
make all

# read in file path
read -p "Please provide a file path to the images you want analyzed: " file_path

# navigate to file_path
cd $file_path

#create folder to hold the output files
mkdir -p output

for FILE in *
do
    if (echo "$FILE" | grep -q "confocal" && grep -q ".tif")
    then
        #file_name_old=$(echo -n "$FILE") #get old file name 
        file_name=$(echo -n "$FILE" | tr -d " ") # removes space
        #touch $file_name
        mv "$FILE" $file_name #rename file to have no spaces 
        #file_name=$(echo -n "$file_name" | tr -d ".tif") # removes .tif from new file name 
        file_name=$(echo -n "$file_name" | cut -d'.' -f1)
        touch output/"${file_name}.csv"
        #echo "./data/Dataset/${file_name}.tif"
        #need to move run into same filepath location as data files
        ./run "${file_name}.tif" > output/"${file_name}.csv"
        #remove first line of output file 
        sed -i '1d' output/"${file_name}.csv"
        #need to add 1 to x and y to coordinates for it to be centered properly in matlab
    fi
done
