#include <stdio.h>
#include <stdlib.h>

//function declarations
int input(int[]);
int input_remove();
int find_score(int[], int, int[]);
void remove_numbers(int[], int[], int[], int, int, int);
void output_result(int, int, int);
int findMax(int[], int);
void duplicate(int[], int[], int);

int main(){

	//variables
	int old_array[50];
	int old_size;
	int new_size;
	int num2remove;
	int original_score;
	int new_score;
	int counter_array[50] = { 0 };

	//function calls
	old_size = input(old_array);
	int old_array2[old_size];
	duplicate(old_array, old_array2, old_size);
	
	num2remove = input_remove();
	
	new_size = old_size - num2remove;
	int new_array[new_size];
	original_score = find_score(old_array, old_size, counter_array);
	remove_numbers(old_array2, new_array, counter_array, num2remove, old_size, new_size);
	new_score = find_score(new_array, new_size, old_array);
	output_result(original_score, new_score, num2remove);
	

	return 0;
}

int input(int arr[]){
	int num;
	int index = 0;

	printf("\nEnter data now: ");
	while(1){
		scanf("%d", &num);
		if(num < 0){
			break;
		} else {
			arr[index] = num;
			index++;
		}
	}
	printf("\n");
	return index;
}

int input_remove(){
	int removal;
	printf("Enter number of elements to remove: ");
	scanf("%d", &removal);
	return removal;
}

int find_score(int arr[], int size, int c_array[]){
	int i = 0;
	int score = 0;
	int curr;
	int curr_index;
	int count;
	
	while(i < size){
		if(arr[i] != -1){
			count = 1;
			curr = arr[i];
			curr_index = i;
			for(int k = i + 1; k < size; k++){
				if(curr == arr[k]){
					arr[curr_index] = -1;
					arr[k] = -1;
					count++;
				}
			}
			c_array[curr_index] = count;
			score += count*count;
			i++;
		}else{
			i++;
		}
	}

	return score;
}
void remove_numbers(int old_arr[], int new_arr[], int c_array[], int rem, int old, int new){
	
	while(rem > 0){
		int max_occur = findMax(c_array, old);
		rem--;
		c_array[max_occur]--;
	}
	
	int k = 0;
	int i = 0;
	while(1){
		
		while(c_array[k] > 0){
			new_arr[i] = old_arr[k];
			c_array[k]--;
			i++;
		}
		k++;

		if(k == old)
			break;
		
	}
	
	



}

int findMax(int arr[], int size){
	int max = 0;
	int max_i = 0;
	for(int i = 0; i < size; i++){
		if(arr[i] > max){
			max = arr[i];
			max_i = i;
		}
	}
	return max_i;
}

void duplicate(int arr[], int arr2[], int size){
	for(int i = 0; i < size; i++){
		arr2[i] = arr[i];
	}
}
void output_result(int og, int new, int rem){
	printf("\nScore of original data set: %d\n", og);
	printf("Score after %d element(s) removed: %d\n\n", rem, new);
}



