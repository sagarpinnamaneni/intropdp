/*  Sagar
 *  Pinnamaneni
 *  sagarpin
 */

#ifndef A1_HPP
#define A1_HPP
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <mpi.h>

void merge(std::vector<short int> &recvBuff, std::vector<short int> &tempVec, int left, int m, int right);
void mergeSort(std::vector<short int> &recvBuff, std::vector<short int> &tempVec, int left, int right);
void Display(std::vector<short int> &vec);

void isort(std::vector<short int>& Xi, MPI_Comm comm) {
    
    int rank, depth, nodeSize;
    MPI_Comm_size(MPI_COMM_WORLD, &nodeSize);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int smallarr = Xi.size()/nodeSize; //the partition size for each processor
    std::vector<short int> localBuf(smallarr,0);
    std::vector<short int> temparr;
    std::vector<short int> finalarr;
    MPI_Scatter(Xi.data(), Xi.size(), MPI_INT, localBuf.data(), smallarr, MPI_INT, 0, MPI_COMM_WORLD);
    mergeSort(localBuf, temparr, 0, (localBuf.size()-1));
    if(rank == 0){
        finalarr.assign(Xi.size(), 0);
    }
    MPI_Gather(localBuf.data(), Xi.size(), MPI_INT, finalarr.data(), Xi.size(), MPI_INT, 0, MPI_COMM_WORLD);
    if(rank == 0){
        std::vector<short int> temp;
        mergeSort(finalarr, temp, 0, Xi.size()-1);
        std::copy(finalarr.begin(), finalarr.end(), std::back_inserter(Xi));
    }
    //final output of array
    std::cout << "sorted vectir is:" << std::endl;
    Display(Xi);

} // isort

void mergeSort(std::vector<short int> &recv, std::vector<short int> &temparr, int left, int right){
    int m;
    if(left < right){
        m = (left + right)/2;
        mergeSort(recv, temparr, left, m);
        mergeSort(recv, temparr, m+1, right);
        merge(recv, temparr, left, m, right);
    }
}


void merge(std::vector<short int> &recv, std::vector<short int> &temparr, int left, int m, int right){
    int i;
    int j = m+1;
    int depth=i=left;
    int k;
    
    while(depth <= m && j <= right){
        if(recv[depth] <= recv[j]){
            temparr[i] = recv[depth];
            depth++;
        }else{
            temparr[i] = recv[j];
            j++;
        }
        i++;
    }
    if(m < depth){
        for(k = j; k <= right; k++){
            temparr[i] = recv[k];
            i++;
        }
    }else{
        for(k = depth; k <= m; k++){
            temparr[i] = recv[k];
            i++;
        }
    }
    for(k = left; k <=right; k++){
        recv[k] = temparr[k];
    }
}



void Display(std::vector<short int> &vec){
    for(auto i : vec){
        std::cout << i << ' ';
    }
    std::cout << std::endl;
}

#endif // A1_HPP
