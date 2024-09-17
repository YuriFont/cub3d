#!/bin/bash

./cub3D 2> stderr_output
cr_cub=$?

grep -q "Error: cub3D only accepts one parameter" stderr_output
cr_grep=$?

if [ $cr_cub -ne 1 ] || [ $cr_grep -ne 0 ]; then
    echo "Error in test 01: ./cub3D"
    exit 1
fi

./cub3D test test 2> stderr_output
cr_cub=$?

grep -q "Error: cub3D only accepts one parameter" stderr_output
cr_grep=$?

if [ $cr_cub -ne 1 ] || [ $cr_grep -ne 0 ]; then
    echo "Error in test 02: ./cubeD test test"
    exit 1
fi

./cub3D test 2> stderr_output
cr_cub=$?

grep -q "Error: the file must have a .cub extension" stderr_output
cr_grep=$?

if [ $cr_cub -ne 1 ] || [ $cr_grep -ne 0 ]; then
    echo "Error in test 03: ./cubeD test"
    exit 1
fi

./cub3D .cub 2> stderr_output
cr_cub=$?

grep -q "Error: the file must have a .cub extension" stderr_output
cr_grep=$?

if [ $cr_cub -ne 1 ] || [ $cr_grep -ne 0 ]; then
    echo "Error in test 04: ./cubeD .cub"
    exit 1
fi

./cub3D ./maps/default.cub 2> stderr_output
cr_cub=$?

if [ $cr_cub -ne 0 ] || [ $cr_grep -ne 0 ]; then
    echo "Error in test 05: ./cub3D ./maps/default.cub"
    exit 1
fi

rm stderr_output
