#!/bin/bash

####### PLANEX SPECIFIC - DO NOT EDIT THIS SECTION
#SBATCH --clusters=faculty
#SBATCH --partition=planex
#SBATCH --qos=planex
#SBATCH --account=cse570f21
#SBATCH --exclusive
#SBATCH --mem=64000
#SBATCH --output=%j.stdout
#SBATCH --error=%j.stderr

####### CUSTOMIZE THIS SECTION FOR YOUR JOB
#SBATCH --job-name="changeme"
#SBATCH --nodes=4
#SBATCH --ntasks-per-node=10
#SBATCH --time=00:15:00

module load export I_MPI_PMI_LIBRARY=/usr/lib64/libpmi.so

## if using Intel MPI add need this
## export I_MPI_PMI_LIBRARY=/usr/lib64/libpmi.so

srun --mpi=pmi2 ./a1 10