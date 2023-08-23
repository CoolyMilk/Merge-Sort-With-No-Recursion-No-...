#include <stdlib.h>
#include <stdio.h>

// Sorry if some stuff looks weird, I had to shave off some space but it wasn't enough
void no_recursion_merge_sort(int *array, int size) {
    int holder[size], marker[size], i, j, length = size;
    
    for (i = 0; i<size; i++) { 
      marker[i] = 1; 
    }
    
    while (length > 1) {
        int passes = length/2, location = 0;
        
        for (i = 0; i < passes; i++) {
            int real_i = i*2;
            int total_length = marker[real_i] + marker[real_i+1];
            
            int left_start = location, left_end = location + marker[real_i];
            int right_start = left_end, right_end = location + total_length;
            
            for (j = 0; j < total_length; j++) {
                if (left_start >= left_end) {
                    holder[j] = array[right_start];
                    right_start++;
                } else if (right_start >= right_end) {
                    holder[j] = array[left_start];
                    left_start++;
                } else {
                    int a = array[left_start];
                    int b = array[right_start];
                    
                    if (a > b) {
                        holder[j] = b;
                        right_start++;
                    } else {
                        holder[j] = a;
                        left_start++;
                    }
                }
            }
            
            for (j = 0; j < total_length; j++) { 
                array[location+j] = holder[j]; 
            }
            location += total_length;
            marker[i] = total_length;
        }
        
        if (passes*2 != length) {
            marker[passes] = marker[length-1];
            length = passes+1;
        } else {
            length = passes;
        }
        
    }

}

int main(int argc, char **argv) {
  	int test[] = {123, 93729, 298392, 0, -293, 3927, 23842};
    int l = sizeof(test)/sizeof(int);
    no_recursion_merge_sort(&test, l);

    // I could have placed it in a function but I'm only going to use it once here soo
    printf("Final Sorted Array : \n[");
    for (int i = 0; i < l; i++){
    	printf("%d, ", test[i]);
    } 
    printf("]\n");
    
