#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define init_size 20
#define popu_size 100

typedef unsigned char uc;

void print_array(uc m[init_size][init_size]);
bool check_surrounding_ones(int arr[init_size][init_size], int row, int col);
uc** create_array();
void free_array(uc ***m);

uc (*apply_rule(uc current[init_size][init_size], uc *rule_vector))[init_size];
int check_neighbors(uc grid[init_size][init_size], int x, int y);




int main(void){
    srandom(time(NULL));
    //Initializing the init_espace
    uc m[init_size][init_size];
    for(int i=0; i<init_size; i++){
        for(int j=0; j<init_size; j++){
            m[i][j] = 0;
        }
    }
    m[init_size-1][init_size/2] = 1;
    print_array(m);


    //Initializing the popu
    uc popu[popu_size][9];
    for(int i=0; i<popu_size; i++){
        for(int j=0; j<9; j++){
            popu[i][j] = rand() % 2;
        }
    }
    
}

/*=*=*=*=*=*=*=*==*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/


int eval(uc m[init_size][init_size], uc popu[popu_size][9]){
    int poggers = 0;
    int pnts_max = 0;

    for(int i=0; i<popu_size; i++){
        if(test(m, popu[i]) > pnts_max){
            poggers = i;
        }
    }

    return poggers;
}

int test(uc m[init_size][init_size], uc rule[9]){
    int pnts = 0;

    uc **next = create_array();
    next = apply_rule(m, rule);

    for(int k=0; k<10; k++){
        for(int i=0; i<init_size; i++){
            for(int j=0; j<init_size; j++){
                if(next[i][j] == 1){
                    pnts+=2;
                    if(check_surrounding_ones(next, i, j)){
                        pnts--;
                    }
                }
            }
        }
        next = apply_rule(next, rule);
    }

    free_array(&next);

    return pnts;


}

/*=*=*=*=*=*=*=*==*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/


// Function to apply the rule based on the locations of the neighbors' 1s
uc (*apply_rule(uc current[init_size][init_size], uc *rule_vector))[init_size] {
    static uc next[init_size][init_size];  // Static array to hold the result

    // Reset the next array to zero for each call
    for (int i = 0; i < init_size; i++) {
        for (int j = 0; j < init_size; j++) {
            next[i][j] = 0;
        }
    }

    // Apply rules to each cell based on neighbors' 1s location
    for (int i = 0; i < init_size; i++) {
        for (int j = 0; j < init_size; j++) {
            int neighbor_config = check_neighbors(current, i, j);

            // Apply the rule based on the pattern of 1s around the cell
            next[i][j] = rule_vector[neighbor_config];
        }
    }

    return next;  // Return the pointer to the static array
}

// Function to check the neighbors of a cell and return a configuration value
int check_neighbors(uc grid[init_size][init_size], int x, int y) {
    int config = 0;

    // Relative positions around the cell (top-left, top, top-right, left, right, bottom-left, bottom, bottom-right)
    int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

    // Check all 8 neighbors
    for (int k = 0; k < 8; k++) {
        int nx = x + dx[k];
        int ny = y + dy[k];

        // Ensure neighbors are within bounds
        if (nx >= 0 && nx < init_size && ny >= 0 && ny < init_size) {
            // Check if the neighbor is '1' and update the config
            if (grid[nx][ny] == 1) {
                config |= (1 << k);  // Set the bit corresponding to the neighbor's position
            }
        }
    }

    return config;  // Return the neighbor configuration as a bitmask
}


/*=*=*=*=*=*=*=*==*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/


// Function to check if there's a 1 in the surrounding neighborhood of the element at (row, col)
bool check_surrounding_ones(int arr[init_size][init_size], int row, int col) {
    // Iterate over the 3x3 grid centered around arr[row][col]
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            // Calculate the neighboring row and column
            int new_row = row + i;
            int new_col = col + j;

            // Skip the center element (itself)
            if (i == 0 && j == 0) {
                continue;
            }

            // Check if the neighboring index is within bounds
            if (new_row >= 0 && new_row < init_size && new_col >= 0 && new_col < init_size) {
                // If there's a 1 in the neighborhood
                if (arr[new_row][new_col] == 1) {
                    return true;
                }
            }
        }
    }
    
    // No 1 found in the neighborhood
    return false;
}

uc** create_array(){
    uc **m = (uc**) malloc(init_size * sizeof(uc*));
    for (int i = 0; i < init_size; i++){
        m[i] = (uc*) malloc(init_size * sizeof(uc));
    }
    return m;
}

void free_array(uc ***m){
    for (int i = 0; i < init_size; i++){
        free((*m)[i]);
    }
    free(*m);  
    *m = NULL;
}

void print_array(uc m[init_size][init_size]){
    for(int i=0; i<init_size; i++){
        for(int j=0; j<init_size; j++){
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }
}