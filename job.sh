#!/bin/bash
#SBATCH --job-name=matrix_multiplication
#SBATCH --output=output.txt
#SBATCH --error=error.txt
#SBATCH --ntasks=2

module load singularity

SINGULARITY_IMAGE=matrix_multiplication.sif

export TMPDIR=$HOME/tmp
mkdir -p $TMPDIR

singularity exec --bind $TMPDIR:/tmp $SINGULARITY_IMAGE /bin/bash -c "export OMPI_MCA_tmpdir_base=$TMPDIR && mpirun -np 2 /app/project/main"