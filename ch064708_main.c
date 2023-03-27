#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;

// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void merge(int array[], int l, int m, int r){
  int i, j, k;
  int n1 = m - l+1;
  int n2 = r - m;
  
// create temp arrays
int L[n1], R[n2];

// copy data to temp arrays L[] and R[]
for (i = 0; i < n1; i++)
    L[i] = array[l + i];
for (j = 0; j < n2; j++)
    R[j] = array[m + 1 + j];

// merge the temp arrays back into arr[l..r]
i = 0; // initial index of first subarray
j = 0; // initial index of second subarray
k = l; // initial index of merged subarray
while (i < n1 && j < n2) {
    if (L[i] <= R[j]) {
        array[k] = L[i];
        i++;
    }
    else {
        array[k] = R[j];
        j++;
    }
    k++;
}

// copy the remaining elements of L[]  
while (i < n1){
    array[k] = L[i];
    i++;
    k++;
}

// copy the remaining elements of R[]
while (j < n2) {
    array[k] = R[j];
    j++;
    k++;
}
}

void mergeSortHelper(int array[], int l, int r){
  if (l < r){
    // find the middle point
    int m = l + (r - l) / 2;

    // recursively sort the first and second halves
    mergeSortHelper(array, l, m);
    mergeSortHelper(array, m + 1, r);

    // merge the sorted halves
    merge(array, l, m, r);
  }
}

void mergeSort(int pData[], int l, int r)
{
  mergeSortHelper(pData, l, r);
}

// implement insertion sort
// extraMemoryAllocated counts bytes of memory allocated
void insertionSort(int* pData, int n)
{
  int i, key, j;
  extraMemoryAllocated = 0;
  for (i = 1; i < n; i++) {
    key = pData[i];
    j = i - 1;
    while (j >= 0 && pData[j] > key) {
      pData[j + 1] = pData[j];
      j = j - 1;
    }
    pData[j + 1] = key;
  }
}

// implement bubble sort
// extraMemoryAllocated counts bytes of extra memory allocated
void bubbleSort(int* pData, int n)
{
  int i, j, temp;
  for (i = 0; i < n-1; i++)
  {
    for (j = 0; j < n-i-1; j++)
    {
      if (pData[j] > pData[j+1])
      {
        // swap pData[j] and pData[j+1]
        temp = pData[j];
        pData[j] = pData[j+1];
        pData[j+1] = temp;
      }
    }
  }
}

// implement selection sort
// extraMemoryAllocated counts bytes of extra memory allocated
void selectionSort(int* pData, int n)
{
  int i, j, min_idx, temp;
  for (i =0; i < n-1; i++)
  {
    // Find the minimum element in unsorted subarray
    min_idx = i;
    for (j = i+1; j < n; j++)
    {
      if (pData [j] < pData[min_idx])
      {
        min_idx = j;
      }
    }
    // Swap the found minimum element with the first element
    temp = pData[min_idx];
    pData[min_idx] = pData[i];
    pData[i] = temp;
    }
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// Implement parse data block
    for (int i = 0; i < dataSz; i++)
    {
      fscanf(inFile, "%d\n", &(*ppData)[i]);
    }  
  }
  fclose(inFile);
  return dataSz;
}

// it prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = {"input1.txt", "input2.txt", "input3.txt"};
	
	for (i=0;i<3;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Selection Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		selectionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Insertion Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		insertionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Bubble Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		bubbleSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}