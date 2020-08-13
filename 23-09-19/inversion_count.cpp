#include<iostream> 

long inversions;

void merge(long arr[], int left, int center, int right) { 
	int i, j, k; 
	int n1 = center - left + 1;
	int n2 = right - center; 

	long L[n1], R[n2]; 

	for (i = 0; i < n1; i++) 
		L[i] = arr[left + i]; 
	for (j = 0; j < n2; j++) 
		R[j] = arr[center + 1+ j]; 

	i = 0; 
	j = 0;
	k = left;  

	while (i < n1 && j < n2) { 
		if (L[i] <= R[j]) { 
			arr[k++] = L[i++]; 
		} 
		else
		{   
      inversions += n1 - i;
			arr[k++] = R[j++]; 
		} 
	} 

	while (i < n1) 
	{ 
		arr[k++] = L[i++];
	} 

	while (j < n2) 
	{ 
		arr[k++] = R[j++]; 
	} 
} 

void merge_sort(long arr[], int left, int right) { 
	if (left < right) { 
		
		int center = left + (right - left)/2; 

		merge_sort(arr, left, center); 
		merge_sort(arr, center + 1, right); 

		merge(arr, left, center, right); 
	} 
}

int main() { 
    int num_tests;
    std::cin >> num_tests;
    for(int i = 0; i < num_tests; i++) {
        int size;
        std::cin >> size;
        long arr[size];
        for(int j = 0; j < size; j++){
            std::cin >> arr[j];
        }
        inversions=0;
        merge_sort(arr, 0, size-1);
        std::cout << inversions << std::endl;
    }
	return 0; 
} 