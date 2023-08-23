#include <stdlib.h>
#include <stdio.h>

// Sorry if some stuff looks weird, I had to shave off some space but it wasn't enough!
void no_recursion_merge_sort(int *array, int size) {
    int holder[size], marker[size], length = size; 
    // Stuff to simulate 'recursion'!
    
    for (int i = 0; i<size; i++) { 
        marker[i] = 1; 
    } // Setting up every individual element as 'arrays' of one!
    
    // Marker just keep tracks of 'sub arrays'!
    
    while (length > 1) { // I think it's just faster to do it this way instead of calculating how much iterations is required using square root!
        int passes = length/2, location = 0;

        /* Passes is just how much arrays left after combining it.
           There is a case where an odd array won't be paired
           but it's fixed at the end of the iteration */
        
        for (int i = 0; i < passes; i++) {
            // Skipping indexes to pair them by two!
            int real_i = i*2;
            int total_length = marker[real_i] + marker[real_i+1];

            // Making indexes to simulate the merge thing!
            int left_start = location, left_end = location + marker[real_i];
            int right_start = left_end, right_end = location + total_length;

            // Placing it in holder so it doesn't write over itself!
            // Mergeeee!!
            for (int j = 0; j < total_length; j++) {
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
            // Transferring the sorted array back into the original!
            for (int j = 0; j < total_length; j++) { 
                array[location+j] = holder[j]; 
            }
            
            // Updating the new array in marker!
            location += total_length;
            marker[i] = total_length;
        }

        /* It will scoot the not paired array if it exists
           back next with the others so it doesn't get forgotten!*/
        if (passes*2 != length) {
            marker[passes] = marker[length-1];
            length = passes+1;
        } else {
            length = passes;
        }
        
    }

}

/*

Basically
(I just replaced the unused 1s with 0s
so you won't get confused, but in reality
they are just previous length values that 
just sit there unused)

holder = {1, 1, 1, 1, 1};
array  = {4, 3, 2, 1, 0};

holder = {2, 2, 1, 0, 0}; 
array  = {3, 4, 1, 2, 0};

holder = {4, 1, 0, 0, 0};
array  = {1, 2, 3, 4, 0};

holder = {5, 0, 0, 0, 0};
array  = {0, 1, 2, 3, 4};

Sorted!!

Not sure if it's 100% sorted for all cases though
but if it works with a tiny array, it should work with a
larger array?
*/


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
}
    
