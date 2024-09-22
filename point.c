#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

#define init_size 30
#define popu_size 100
#define mut 0.1
#define gen 100

typedef unsigned char uc;

void print_array(uc m[init_size][init_size]);
bool check_surrounding_ones(uc arr[init_size][init_size], int row, int col);
uc** create_array();
void free_array(uc ***m);
void results(uc m[init_size][init_size], uc rule[256]);

uc (*apply_rule(uc current[init_size][init_size], uc *rule_vector))[init_size];
int check_neighbors(uc grid[init_size][init_size], int x, int y);

int eval(uc m[init_size][init_size], uc popu[popu_size][256]);
int test(uc m[init_size][init_size], uc rule[256]);

uc (*sexo(uc popu[popu_size][256], int poggers))[256];



int main(void){
    srandom(time(NULL));
    //Initializing the init_espace
    uc m[init_size][init_size];
    for(int i=0; i<init_size; i++){
        for(int j=0; j<init_size; j++){
            m[i][j] = 0;
        }
    }
    //Initializing a square
    for(int i=0; i<init_size/4; i++){
        m[init_size/4+i][1] = 1;
        m[init_size/4+i][init_size/4] = 1;

        m[init_size/4][1+i] = 1;
        m[init_size/4+6][1+i] = 1;
    }
    //print_array(m);


    //Initializing the popu
    uc popu[popu_size][256];
    for(int i=0; i<popu_size; i++){
        for(int j=0; j<256; j++){
            popu[i][j] = rand() % 2;
        }
    }

    //Generations
    int poggers = eval(m, popu);
    uc (*next_popu)[256] = sexo(popu, poggers);
    for(int i=0; i<gen; i++){
        poggers = eval(m, next_popu);
        next_popu = sexo(next_popu, poggers);
    }

    results(m, next_popu[eval(m, next_popu)]);

    printf("\n%d\n", eval(m, next_popu));
    
}

/*=*=*=*=*=*=*=*==*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/


int eval(uc m[init_size][init_size], uc popu[popu_size][256]){
    int poggers = -1;
    int pnts_max = -1;
    int pnts = 0;

    for(int i=0; i<popu_size; i++){
        pnts = test(m, popu[i]);
        if(pnts > pnts_max){
            pnts_max = pnts;
            poggers = i;
        }
    }
    printf("%d ", pnts_max);
    fflush(stdout);

    return poggers;
}

int test(uc m[init_size][init_size], uc rule[256]){
    int pnts = 0;

    uc (*next)[init_size] = apply_rule(m, rule);

    for(int k=0; k<20; k++){
        for(int i=0; i<init_size; i++){
            for(int j=0; j<init_size; j++){
                if(next[i][j] == 1){
                    if(next[i][j+1] == 0){
                        pnts++;
                    }
                    if(next[i][j-1] == 0){
                        pnts--;
                    }
                }
                if(next[i][j] == 0){
                    if(next[i][j+1] == 1){
                        pnts++;
                    }
                    if(next[i][j-1] == 1){
                        pnts--;
                    }
                }
            }
        }
        next = apply_rule(next, rule);
    }

    return pnts;


}

/*=*=*=*=*=*=*=*==*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/


uc (*sexo(uc popu[popu_size][256], int poggers))[256]{
    static uc next[popu_size][256];

    //Copying popu to next
    for (int i=0; i < popu_size; i++){
        for(int j=0; j<256; j++){
            next[i][j] = popu[i][j];
        }
    }
    

    for(int i=0; i<popu_size; i++){
        if(i == poggers) continue;
        int mutations = 256*mut;
        for(int j=0; j<mutations; j++){
            next[i][random() % 256] = random() % 2;
        }
    }

    return next;
}


/*=*=*=*=*=*=*=*==*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/


uc (*apply_rule(uc current[init_size][init_size], uc *rule_vector))[init_size]{
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


void results(uc m[init_size][init_size], uc rule[256]){
    uc (*next)[init_size] = apply_rule(m, rule);

    sleep(1);
    system("clear");

    for(int k=0; k<20; k++){
        printf("%d\n", k+1);
        for(int i=0; i<init_size; i++){
            for(int j=0; j<init_size; j++){
                printf("%d ", next[i][j]);
            }
            printf("\n");
        }
        // Wait for 1 second
        k==0 ? sleep(3) : sleep(1);
        
        // Clear the terminal screen
        k==20-1 ?  : system("clear");

        next = apply_rule(next, rule);
    }
}

// Function to check if there's a 1 in the surrounding neighborhood of the element at (row, col)
bool check_surrounding_ones(uc arr[init_size][init_size], int row, int col) {
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
    printf("---------------------------------\n");
}