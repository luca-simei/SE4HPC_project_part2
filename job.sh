#!/bin/bash
#SBATCH --job-name=matrix_multiplication
#SBATCH --output=output.txt
#SBATCH --error=error.txt
#SBATCH --ntasks=2

singularity run matrix_multiplication.sif
singularity stop matrix_multiplication.sif