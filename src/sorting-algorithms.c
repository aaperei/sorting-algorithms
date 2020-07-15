/*
 =========================================================================
 Name        : sorting.c
 Author      : Alison Augusto Miranda Pereira
 Description : Comparison of Main Sorting Algorithms
 =========================================================================
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include<time.h>
#include <inttypes.h>

typedef int Tkey;
typedef struct TItem {
	Tkey key;
//Add here any other attributes as needed
} TItem;

char *SHELL_SORT = "Shell Sort";
char *INSERTION_SORT = "Insertion Sort";
char *SELECTION_SORT = "Selection Sort";
char *BUBBLE_SORT = "Bubble Sort";
char *MERGE_SORT = "Merge Sort";
char *QUICK_SORT = "Quick Sort";
char *HEAP_SORT = "Heap Sort";

char *RANDOM = "RANDOM";
char *SORTED = "SORTED";
char *REVERSED_SORTED = "REVERSED_SORTED";
char *NINETY_PERCENT_SORTED = "NINETY_PERCENT_SORTED";

struct TItem items10Reference[10];
struct TItem items100Reference[100];
struct TItem items1000Reference[1000];
struct TItem items10000Reference[10000];
struct TItem items100000Reference[100000];
struct TItem items1000000Reference[1000000];

struct TItem items10[10];
struct TItem items100[100];
struct TItem items1000[1000];
struct TItem items10000[10000];
struct TItem items100000[100000];
struct TItem items1000000[1000000];

long long int numberOfKeyComparisons;
long long int numberOfRecordMovements;

clock_t startTime;
clock_t endTime;

FILE *outputFile;
/*
 =========================================================================
 Below you can find some auxiliary methods used to initialize the arrays
 and store the results into a text file
 =========================================================================
 */

void copyItemIntoReference(TItem *items, TItem *itemsReference, int n) {
	int i;

	for (i = 0; i < n; i++) {
		items[i].key = itemsReference[i].key;
	}
}

void copyItems() {
	copyItemIntoReference(items10, items10Reference, 10);
	copyItemIntoReference(items100, items100Reference, 100);
	copyItemIntoReference(items1000, items1000Reference, 1000);
	copyItemIntoReference(items10000, items10000Reference, 10000);
	copyItemIntoReference(items100000, items100000Reference, 100000);
	copyItemIntoReference(items1000000, items1000000Reference, 1000000);
}

void printComplexity(char *algorithmName, int n, char *initialCondition) {
	clock_t end = clock();
	long long int cpuCyclesUsed = ((double) (end - startTime));

	fprintf(outputFile, "%s\t", algorithmName);
	fprintf(outputFile, "%d\t", n);
	fprintf(outputFile, "%s\t", initialCondition);
	fprintf(outputFile, "%lld\t", numberOfKeyComparisons);
	fprintf(outputFile, "%lld\t", numberOfRecordMovements);
	fprintf(outputFile, "%lld\n", cpuCyclesUsed);

	fflush(outputFile);
}

void initializeItemsWithAscendingValues() {
	int i = 0;

	for (i = 0; i < 10; i++) {
		items10Reference[i].key = i;
	}

	for (i = 0; i < 100; i++) {
		items100Reference[i].key = i;
	}

	for (i = 0; i < 1000; i++) {
		items1000Reference[i].key = i;
	}

	for (i = 0; i < 10000; i++) {
		items10000Reference[i].key = i;
	}

	for (i = 0; i < 100000; i++) {
		items100000Reference[i].key = i;
	}

	for (i = 0; i < 1000000; i++) {
		items1000000Reference[i].key = i;
	}

}

void initializeItemsWithDescendingValues() {
	int i = 0;
	int j=0;

	for (i = 9; i >= 0; i--) {
		items10Reference[i].key = j;
		j++;
	}

	j=0;
	for (i = 99; i >= 0; i--) {
		items100Reference[i].key = j;
		j++;
	}

	j=0;
	for (i = 999; i >= 0; i--) {
		items1000Reference[i].key = j;
		j++;
	}

	j=0;
	for (i = 9999; i >= 0; i--) {
		items10000Reference[i].key = j;
		j++;
	}

	j=0;
	for (i = 99999; i >= 0; i--) {
		items100000Reference[i].key = j;
		j++;
	}

	j=0;
	for (i = 999999; i >= 0; i--) {
		items1000000Reference[i].key = j;
		j++;
	}
}

void initializeItems90PercentSorted() {
	int i = 0;
	TItem temp;

	initializeItemsWithAscendingValues();

	srand(time(0));
	for (i = 0; i < 1; i++) {
		int randomIndex = rand() % 10;
		temp = items10Reference[i];
		items10Reference[i] = items10Reference[randomIndex];
		items10Reference[randomIndex] = temp;
	}

	srand(time(0));
	for (i = 0; i < 10; i++) {
		int randomIndex = rand() % 100;
		temp = items100Reference[i];
		items100Reference[i] = items100Reference[randomIndex];
		items100Reference[randomIndex] = temp;
	}

	srand(time(0));
	for (i = 0; i < 100; i++) {
		int randomIndex = rand() % 1000;
		temp = items1000Reference[i];
		items1000Reference[i] = items1000Reference[randomIndex];
		items1000Reference[randomIndex] = temp;
	}

	srand(time(0));
	for (i = 0; i < 1000; i++) {
		int randomIndex = rand() % 10000;
		temp = items10000Reference[i];
		items10000Reference[i] = items10000Reference[randomIndex];
		items10000Reference[randomIndex] = temp;
	}

	srand(time(0));
	for (i = 0; i < 10000; i++) {
		int randomIndex = rand() % 100000;
		temp = items100000Reference[i];
		items100000Reference[i] = items100000Reference[randomIndex];
		items100000Reference[randomIndex] = temp;
	}

	srand(time(0));
	for (i = 0; i < 100000; i++) {
		int randomIndex = rand() % 1000000;
		temp = items1000000Reference[i];
		items1000000Reference[i] = items1000000Reference[randomIndex];
		items1000000Reference[randomIndex] = temp;
	}
}

void initializeItemsWithRandomValues() {
	int i = 0;
	TItem temp;

	initializeItemsWithAscendingValues();

	srand(time(0));
	for (i = 0; i < 10; i++) {
		int randomIndex = rand() % 10;
		temp = items10Reference[i];
		items10Reference[i] = items10Reference[randomIndex];
		items10Reference[randomIndex] = temp;
	}

	srand(time(0));
	for (i = 0; i < 100; i++) {
		int randomIndex = rand() % 100;
		temp = items100Reference[i];
		items100Reference[i] = items100Reference[randomIndex];
		items100Reference[randomIndex] = temp;
	}

	srand(time(0));
	for (i = 0; i < 1000; i++) {
		int randomIndex = rand() % 1000;
		temp = items1000Reference[i];
		items1000Reference[i] = items1000Reference[randomIndex];
		items1000Reference[randomIndex] = temp;
	}

	srand(time(0));
	for (i = 0; i < 10000; i++) {
		int randomIndex = rand() % 10000;
		temp = items10000Reference[i];
		items10000Reference[i] = items10000Reference[randomIndex];
		items10000Reference[randomIndex] = temp;
	}

	srand(time(0));
	for (i = 0; i < 100000; i++) {
		int randomIndex = rand() % 100000;
		temp = items100000Reference[i];
		items100000Reference[i] = items100000Reference[randomIndex];
		items100000Reference[randomIndex] = temp;
	}

	srand(time(0));
	for (i = 0; i < 1000000; i++) {
		int randomIndex = rand() % 1000000;
		temp = items1000000Reference[i];
		items1000000Reference[i] = items1000000Reference[randomIndex];
		items1000000Reference[randomIndex] = temp;
	}
}

void initializeStructs(char *inputType) {

	if (strcmp(inputType, RANDOM) == 0) {
		initializeItemsWithRandomValues();

	} else if (strcmp(inputType, SORTED) == 0) {
		initializeItemsWithAscendingValues();

	} else if (strcmp(inputType, REVERSED_SORTED) == 0) {
		initializeItemsWithDescendingValues();

	} else if (strcmp(inputType, NINETY_PERCENT_SORTED) == 0) {
		initializeItems90PercentSorted();
	}

}

/*
 =========================================================================
 Below you can find the implementation for the following algorithms:
 - Shell Sort
 - Insertion Sort
 - Selection Sort
 - Bubble Sort
 - Heap Sort
 - Merge Sort
 - Quick Sort

   * parameter: items -> Array of TItem elements
   * parameter: n -> Length of items

 *SHELL SORT DESCRIPTION:
 This method sorts and array of TItem (ascending way)  using Shell Sort Algorithm
 It splits the initial array in smaller subarrays where the elements are distant apart
 This distance (gap) among the subarray elements starts from floor(n/2)
 and at each iteration we keep reducing the gap dividing its value by 2 while  it's greater than 0
 At last iteration Shell Sort works exactly as the common Insertion Sort Algorithm
 =========================================================================
 */

void shellSort(TItem *items, int n) {
	TItem temp;
	int i, j, gap;

	startTime = clock();
	numberOfKeyComparisons = 0;
	numberOfRecordMovements = 0;

	for (gap = n / 2; gap > 0; gap /= 2) {
		for (i = gap; i < n; i++) {
			temp = items[i];
			numberOfRecordMovements++;
			for (j = i; j >= gap && items[j - gap].key > temp.key; j -= gap) {
				items[j] = items[j - gap];
				numberOfKeyComparisons++;
				numberOfRecordMovements++;
			}
			numberOfKeyComparisons++;

			items[j] = temp;
			numberOfRecordMovements++;
		}
	}
}

void insertionSort(TItem *items, int n) {
	int i, j;
	TItem temp;

	startTime = clock();
	numberOfKeyComparisons = 0;
	numberOfRecordMovements = 0;

	for (i = 1; i < n; i++) {
		temp = items[i];
		numberOfRecordMovements++;
		j = i - 1;
		while ((j >= 0) && (temp.key < items[j].key)) {
			items[j + 1] = items[j];
			j--;
			numberOfKeyComparisons++;
			numberOfRecordMovements++;
		}
		numberOfKeyComparisons++;
		items[j + 1] = temp;
		numberOfRecordMovements++;
	}
}

void selectionSort(TItem *items, int n) {
	int i, j, min;
	TItem temp;

	startTime = clock();
	numberOfKeyComparisons = 0;
	numberOfRecordMovements = 0;

	for (i = 0; i < n - 1; i++) {
		min = i;
		for (j = i + 1; j < n; j++) {
			numberOfKeyComparisons++;
			if (items[j].key < items[min].key) {
				min = j;
			}
		}

		temp = items[min];
		items[min] = items[i];
		items[i] = temp;
		numberOfRecordMovements += 3;
	}
}

void bubbleSort(TItem *items, int n) {
	int i, j;
	TItem temp;

	numberOfKeyComparisons = 0;
	numberOfRecordMovements = 0;

	startTime = clock();

	for (i = 0; i < n - 1; i++) {
		for (j = 1; j < n - i; j++) {

			numberOfKeyComparisons++;
			if (items[j].key < items[j - 1].key) {
				temp = items[j];
				items[j] = items[j - 1];
				items[j - 1] = temp;
				numberOfRecordMovements += 3;
			}

		}
	}
}

void heapRefaz(TItem *items, int esq, int dir) {
	TItem temp;
	int i, j;
	i = esq;
	j = i * 2 + 1;
	temp = items[i];
	while (j <= dir) {
		numberOfKeyComparisons++;
		if ((j < dir) && (items[j].key < items[j + 1].key)) {
			j++;
		}

		numberOfKeyComparisons++;
		if (temp.key >= items[j].key) {
			break;
		}

		items[i] = items[j];
		numberOfRecordMovements++;

		i = j;
		j = i * 2 + 1;

	}
	items[i] = temp;
	numberOfRecordMovements++;
}

void buildHeap(TItem *items, int n) {
	int esq;
	esq = (n / 2) - 1;
	while (esq >= 0) {
		heapRefaz(items, esq, n - 1);
		esq--;
	}
}

void heapSort(TItem *items, int n) {
	TItem aux;
	int m;

	startTime = clock();
	numberOfKeyComparisons = 0;
	numberOfRecordMovements = 0;

	buildHeap(items, n);
	m = n - 1;
	while (m > 0) {
		aux = items[m];
		items[m] = items[0];
		items[0] = aux;
		numberOfRecordMovements += 3;
		m = m - 1;
		heapRefaz(items, 0, m);
	}
}

void merge(TItem *items, int p, int q, int r) {
	int i, j, k;
	TItem *temp;
	temp = (TItem*) malloc((r - p + 1) * sizeof(TItem));
	for (i = p; i <= q; i++) {
		temp[i - p] = items[i];
		numberOfRecordMovements++;
	}
	for (j = q + 1; j <= r; j++) {
		temp[r + q + 1 - j - p] = items[j];
		numberOfRecordMovements++;
	}
	i = p;
	j = r;
	for (k = p; k <= r; k++) {
		numberOfKeyComparisons++;
		if (temp[i - p].key <= temp[j - p].key) {
			items[k] = temp[i - p];
			numberOfRecordMovements++;
			i = i + 1;
		} else {
			items[k] = temp[j - p];
			numberOfRecordMovements++;
			j = j - 1;
		}
	}
	free(temp);
}

void mergeSort(TItem *items, int n) {
	int p, q, r;
	int salto = 1;

	startTime = clock();
	numberOfKeyComparisons = 0;
	numberOfRecordMovements = 0;

	while (salto < n) {
		p = 0;
		while (p + salto < n) {
			r = p + 2 * salto - 1;
			if (r >= n)
				r = n - 1;
			q = p + salto - 1;
			merge(items, p, q, r);
			p = p + 2 * salto;
		}
		salto = 2 * salto;
	}
}

int quickSort_particao(TItem *items, int p, int r) {
	TItem x, temp;
	int i, j;
	x = items[r];
	numberOfRecordMovements++;
	i = p - 1;
	for (j = p; j <= r - 1; j++) {
		numberOfKeyComparisons++;
		if (items[j].key <= x.key) {
			i = i + 1;
			temp = items[i];
			items[i] = items[j];
			items[j] = temp;
			numberOfRecordMovements += 3;
		}
	}
	temp = items[i + 1];
	items[i + 1] = items[r];
	items[r] = temp;
	numberOfRecordMovements += 3;
	return i + 1;
}

void quickSort_ordena(TItem *items, int p, int r) {
	int q;
	if (p < r) {
		q = quickSort_particao(items, p, r);
		quickSort_ordena(items, p, q - 1);
		quickSort_ordena(items, q + 1, r);
	}
}

void quickSort(TItem *items, int n) {
	startTime = clock();
	numberOfKeyComparisons = 0;
	numberOfRecordMovements = 0;

	quickSort_ordena(items, 0, n - 1);
}

/*
 ============================================================================
 Below you can find some auxiliary methods to execute the previous implemented
 sorting algorithms, for the following conditions
 - N=10, 100, 1000, 10.000, 100.000, 1.000.000
 - INITIALY = RANDOM, SORTED, REVERSED_SORTED, ALMOST_SORTED
 ============================================================================
 */

void runShellSortAndStoreResults(TItem *items, int n, char *inputType) {
	char *algorthmName = SHELL_SORT;
	shellSort(items, n);
	printComplexity(algorthmName, n, inputType);
}

void runShellSort(char *inputType) {
	copyItems();
	runShellSortAndStoreResults(items10, 10, inputType);
	runShellSortAndStoreResults(items100, 100, inputType);
	runShellSortAndStoreResults(items1000, 1000, inputType);
	runShellSortAndStoreResults(items10000, 10000, inputType);
	runShellSortAndStoreResults(items100000, 100000, inputType);
	runShellSortAndStoreResults(items1000000, 1000000, inputType);
}

void runInsertionSortAndStoreResults(TItem *items, int n, char *inputType) {
	char *algorthmName = INSERTION_SORT;
	insertionSort(items, n);
	printComplexity(algorthmName, n, inputType);
}

void runInsertionSort(char *inputType) {
	copyItems();
	runInsertionSortAndStoreResults(items10, 10, inputType);
	runInsertionSortAndStoreResults(items100, 100, inputType);
	runInsertionSortAndStoreResults(items1000, 1000, inputType);
	runInsertionSortAndStoreResults(items10000, 10000, inputType);
	runInsertionSortAndStoreResults(items100000, 100000, inputType);
	runInsertionSortAndStoreResults(items1000000, 1000000, inputType);
}

void runSelectionSortAndStoreResults(TItem *items, int n, char *inputType) {
	char *algorthmName = SELECTION_SORT;
	selectionSort(items, n);
	printComplexity(algorthmName, n, inputType);
}

void runSelectionSort(char *inputType) {
	copyItems();
	runSelectionSortAndStoreResults(items10, 10, inputType);
	runSelectionSortAndStoreResults(items100, 100, inputType);
	runSelectionSortAndStoreResults(items1000, 1000, inputType);
	runSelectionSortAndStoreResults(items10000, 10000, inputType);
	runSelectionSortAndStoreResults(items100000, 100000, inputType);
	runSelectionSortAndStoreResults(items1000000, 1000000, inputType);
}

void runBubbleSortAndStoreResults(TItem *items, int n, char *inputType) {
	char *algorthmName = BUBBLE_SORT;
	bubbleSort(items, n);
	printComplexity(algorthmName, n, inputType);
}

void runBubbleSort(char *inputType) {
	copyItems();
	runBubbleSortAndStoreResults(items10, 10, inputType);
	runBubbleSortAndStoreResults(items100, 100, inputType);
	runBubbleSortAndStoreResults(items1000, 1000, inputType);
	runBubbleSortAndStoreResults(items10000, 10000, inputType);
	runBubbleSortAndStoreResults(items100000, 100000, inputType);
	runBubbleSortAndStoreResults(items1000000, 1000000, inputType);
}

void runQuickSortAndStoreResults(TItem *items, int n, char *inputType) {
	char *algorthmName = QUICK_SORT;
	quickSort(items, n);
	printComplexity(algorthmName, n, inputType);
}

void runQuickSort(char *inputType) {
	copyItems();
	runQuickSortAndStoreResults(items10, 10, inputType);
	runQuickSortAndStoreResults(items100, 100, inputType);
	runQuickSortAndStoreResults(items1000, 1000, inputType);
	runQuickSortAndStoreResults(items10000, 10000, inputType);
	runQuickSortAndStoreResults(items100000, 100000, inputType);
	runQuickSortAndStoreResults(items1000000, 1000000, inputType);
}

void runHeapSortAndStoreResults(TItem *items, int n, char *inputType) {
	char *algorthmName = HEAP_SORT;
	heapSort(items, n);
	printComplexity(algorthmName, n, inputType);
}

void runHeapSort(char *inputType) {
	copyItems();
	runHeapSortAndStoreResults(items10, 10, inputType);
	runHeapSortAndStoreResults(items100, 100, inputType);
	runHeapSortAndStoreResults(items1000, 1000, inputType);
	runHeapSortAndStoreResults(items10000, 10000, inputType);
	runHeapSortAndStoreResults(items100000, 100000, inputType);
	runHeapSortAndStoreResults(items1000000, 1000000, inputType);
}

void runMergeSortAndStoreResults(TItem *items, int n, char *inputType) {
	char *algorthmName = MERGE_SORT;
	mergeSort(items, n);
	printComplexity(algorthmName, n, inputType);
}

void runMergeSort(char *inputType) {
	copyItems();
	runMergeSortAndStoreResults(items10, 10, inputType);
	runMergeSortAndStoreResults(items100, 100, inputType);
	runMergeSortAndStoreResults(items1000, 1000, inputType);
	runMergeSortAndStoreResults(items10000, 10000, inputType);
	runMergeSortAndStoreResults(items100000, 100000, inputType);
	runMergeSortAndStoreResults(items1000000, 1000000, inputType);
}

void runAll(char *inputType) {
	initializeStructs(inputType);

	runShellSort(inputType);
	runInsertionSort(inputType);
	runSelectionSort(inputType);
	runBubbleSort(inputType);
	runQuickSort(inputType);
	runHeapSort(inputType);
	runMergeSort(inputType);
}

int main() {
	outputFile = fopen("c:\\temp\\sorting_output.txt", "w");

	fprintf(outputFile, "Starting Program\n");

	fprintf(outputFile, "CLOCKS_PER_SEC=%ld", CLOCKS_PER_SEC);

	fprintf(outputFile, "\nMethod	N	Initial_Condition	C(n)	M(n)	CPU Cycles Used\n");
	fflush(outputFile);

	runAll(RANDOM);
	runAll(SORTED);
	runAll(REVERSED_SORTED);
	runAll(NINETY_PERCENT_SORTED);

	fclose(outputFile);

	return 0;
}
