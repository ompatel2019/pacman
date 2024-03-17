// COMP1511 Week 5 Lecture 2
// Bubble Tea Adventure!
// Tammy Zhong

#include <stdio.h>

#define MAP_ROWS 6
#define MAP_COLUMNS 8

enum entity {
    PERSON,
    BOBA,
    FOOTPRINT_UP,
    FOOTPRINT_DOWN,
    FOOTPRINT_LEFT,
    FOOTPRINT_RIGHT,
    EMPTY
};

enum place_type {
    SHOP,
    GYM,
    HOME,
    UNDEVELOPED
};

struct location {
    enum entity entity;
    enum place_type place;
};

void initialise_map(struct location map[MAP_ROWS][MAP_COLUMNS]);
void print_map(struct location map[MAP_ROWS][MAP_COLUMNS]);
void print_location(struct location location, int place_print);


//my functions 
int check_valid_inputs(int row, int col);

int main(void) {

    struct location map[MAP_ROWS][MAP_COLUMNS];

    initialise_map(map);

    // TODO get user input of home location 
    int h_row; 
    int h_col;

    printf("Enter the location of home: ");
    scanf("%d %d", &h_row, &h_col); 

    // TODO get user input of shop location 
    int b_row;
    int b_col; 

    printf("Enter the location of boba shop: ");
    scanf("%d %d", &b_row, &b_col);

    //TODO if the inputs are valid 
    if (check_valid_inputs(h_row, h_col) != 1 
        || check_valid_inputs(b_row, b_col) != 1) {
        printf("Enter valid coordinates.\n");
        return 1; 
    }

    //TODO Update the map with boba and home location 

    map[h_row][h_col].place = HOME; 
    map[h_row][h_col].entity = PERSON;
    map[b_row][b_col].place = SHOP; 

    print_map(map);

    // Keep getting user inputs 'u' (up), 'l' (left), 'r' (right), 'd' down,
     















    // update and print the updated map until they find boba store 


    return 0;
}

// return 0 - given points are not valid inputs 
// return 1 - given points are valid inputs 

// STARTER FUNCTIONS BELOW THIS POINT:
int check_valid_inputs(int row, int col) {
    return row >= 0 && row < MAP_ROWS && col >= 0 && col < MAP_COLUMNS; 

}


// initialises the map with empty undeveloped areas
void initialise_map(struct location map[MAP_ROWS][MAP_COLUMNS]) {
    int row = 0;
    while (row < MAP_ROWS) {
        int col = 0;
        while (col < MAP_COLUMNS) {
            map[row][col].place = UNDEVELOPED;
            map[row][col].entity = EMPTY;
            col++;
        }
        row++;
    }
}

// print out the map
void print_map(struct location map[MAP_ROWS][MAP_COLUMNS]) {
    int row = 0;
    while (row < MAP_ROWS * 2) {
        int col = 0;
        while (col < MAP_COLUMNS) {
            print_location(map[row / 2][col], row % 2);
            col++;
        }
        row++;
        printf("\n");
    }

}

// prints specific location on map (used by print_map)
void print_location(struct location location, int place_print) {
    if (place_print) {
        if (location.place == SHOP) {
            printf(" S ");
        } else if (location.place == HOME) {
            printf(" H ");
        } else if (location.place == GYM) {
            printf(" G ");
        } else if (location.place == UNDEVELOPED) {
            printf(" . ");
        } else {
            printf(" ? ");
        }
    } else {

        if (location.entity == EMPTY) {
            printf("   ");
        } else if (location.entity == PERSON) {
            printf("(P)");
        } else if (location.entity == BOBA) {
            printf("(B)");
        } else if (location.entity == FOOTPRINT_UP) {
            printf("(^)");
        } else if (location.entity == FOOTPRINT_RIGHT) {
            printf("(>)");
        } else if (location.entity == FOOTPRINT_DOWN) {
            printf("(v)");
        } else if (location.entity == FOOTPRINT_LEFT) {
            printf("(<)");
        } else {
            printf(" ? ");
        }
    }
}