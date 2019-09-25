#!/bin/bash

target=""
let count=0
for f in input_files/*
do
    name=$(basename $f)
    echo "-------------------------------------------------------------------------------------"
    echo "Running Savings algorihtm on instance " $name
    ./CVRPClarkeAndWrightHeuristicSolver input_files/$name > output_files/$name
    echo "Results are stored in  output_files/"$name 
done
