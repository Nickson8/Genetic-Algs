#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define init_size 20
#define popu_size 100

typedef unsigned char uc;

void print_array(uc m[init_size][init_size]);

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


void print_array(uc m[init_size][init_size]){
    for(int i=0; i<init_size; i++){
        for(int j=0; j<init_size; j++){
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }
}

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