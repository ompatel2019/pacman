// cs_defence.c
//
// This program was written by [Om Patel] (z5480101)
// on [17/03/23]
//
// TODO:

#include <stdio.h>
#include <stdlib.h>

#define MAP_ROWS 6
#define MAP_COLUMNS 12

#define UP 'u'
#define DOWN 'd'
#define LEFT 'l'
#define RIGHT 'r'

////////////////////////////////////////////////////////////////////////////////
/////////////////////////// USER DEFINED TYPES  ////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
enum land_type {
    GRASS,
    WATER,
    PATH_START,
    PATH_END,
    PATH_UP,
    PATH_RIGHT,
    PATH_DOWN,
    PATH_LEFT,
    TELEPORTER
};

enum entity {
    EMPTY,
    ENEMY,
    BASIC_TOWER,
    POWER_TOWER,
    FORTIFIED_TOWER,
};

struct tile {
    enum land_type land;
    enum entity entity;
    int n_enemies;
};

////////////////////////////////////////////////////////////////////////////////
////////////////////////  YOUR FUNCTION PROTOTYPE  /////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// TODO: Put your function prototypes here
void check_valid_enemy_input(int enemies, int start_row, int start_col, 
    int starting_lives, int money, struct tile map[MAP_ROWS][MAP_COLUMNS]);

void print_lake (int lake_row, int lake_col, int lake_height, int lake_width,
    int starting_lives, int money, struct tile map[MAP_ROWS][MAP_COLUMNS]);
    
void find_end_point(int lake_row, int lake_col, int start_row, int start_col,
        int starting_lives, int money, struct tile map[MAP_ROWS][MAP_COLUMNS]);

void spawn_enemies (int num_enemies, int start_row, 
        int start_col, struct tile map[MAP_ROWS][MAP_COLUMNS]);

int add_basic_tower (int tower_row, int tower_col, int money, struct tile map[MAP_ROWS][MAP_COLUMNS]);

int tower_upgrade (int upgrade_row, int upgrade_col, int money, struct tile map[MAP_ROWS][MAP_COLUMNS]); 

void rain_on_map(int row_spacing, int column_spacing, int row_offset, int column_offset, 
    struct tile map[MAP_ROWS][MAP_COLUMNS]);

////////////////////////////////////////////////////////////////////////////////
////////////////////// PROVIDED FUNCTION PROTOTYPE  ////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void initialise_map(struct tile map[MAP_ROWS][MAP_COLUMNS]);
void print_map(struct tile map[MAP_ROWS][MAP_COLUMNS], int lives, int money);
void print_tile(struct tile tile, int entity_print);

int main(void) {
    // This `map` variable is a 2D array of `struct tile`s.
    // It is `MAP_ROWS` x `MAP_COLUMNS` in size (which is 6x12 for this
    // assignment!)
    struct tile map[MAP_ROWS][MAP_COLUMNS];

    // This will initialise all tiles in the map to have GRASS land and EMPTY
    // entity values.
    initialise_map(map);

    // TODO: Stage 1.1 - Scan in lives, money and start/ending points 

    int starting_lives, money;
    int start_row, start_col;
    int end_row, end_col;

    printf("Starting Lives: ");
    scanf("%d", &starting_lives);
    printf("Starting Money($): ");
    scanf("%d", &money);

    printf("Start Point: ");
    scanf("%d %d", &start_row, &start_col);
    map[start_row][start_col].land = PATH_START;

    printf("End Point: ");
    scanf("%d %d", &end_row, &end_col);
    map[end_row][end_col].land = PATH_END;

    print_map(map, starting_lives, money);

    // TODO: Stage 1.2 - Scan in the initial enemies to starting point 

    int enemies;
    printf("Initial Enemies: ");
    scanf("%d", &enemies);

    // Calls function to check input from user regarding number of enemeis 
    check_valid_enemy_input(enemies, start_row, start_col, starting_lives, 
        money, map);    

    int lake_row, lake_col, lake_height, lake_width;
    printf("Enter Lake: ");
    scanf("%d %d %d %d", &lake_row, &lake_col, &lake_height, &lake_width);

    // TODO: Stage 1.3 - Add the ability to create a lake on the map 

    // Function to check if lake dimension inputs are valid and prints 
    // it onto terminal 

    print_lake (lake_row, lake_col, lake_height, lake_width, starting_lives, money, map);

    // Stage 2.1: Add the ability for user to navigate from start point to end point

    // function takes user input to go from starting point to end point 
    // using 'u', 'd', 'l', 'r', commands  
    find_end_point(lake_row, lake_col, start_row, start_col, starting_lives, money, map);

    char entity = 0;
    
    while (printf("Enter Command: ") && scanf(" %c", &entity) !=EOF) {
        if (entity == 'e') {
            // Stage 2.2: Add the ability to spawn enemies at starting 
            // point multiple times
            int num_enemies = 0;
            // function allows user to add enemies to the start point 
            spawn_enemies (num_enemies, start_row, start_col, map);
            print_map(map, starting_lives, money); 
                        

        } else if (entity == 't')  {
            // Stage 2.3: Add the ability to spawn towers at provided row/column 
            int tower_row = 0, tower_col = 0;
            // function returns money used each time a tower is successfully spawned 
            money = add_basic_tower(tower_row, tower_col, money, map);
            print_map(map, starting_lives, money); 
            
        } else if (entity == 'm') {     
            // Stage 3.1: Add the ability for enemies to move from spawn 
            // location to ending location             

        } else if (entity == 'u') {
            // Stage 3.2: Add the ability to upgrade basic tower two times 
            int upgrade_row = 0, upgrade_col = 0;
            // function returns money used each time a tower is successfully upgraded 
            money = tower_upgrade(upgrade_row, upgrade_col, money, map);
            print_map(map, starting_lives, money);

            
        } else if (entity == 'a') { 
            // Stage 3.3: Add the ability for towers to attack enemies  

        } else if (entity == 'r') {
            // Stage 3.4: Add the ability to rain on the map in desired pattern 
            int row_spacing = 0, column_spacing = 0;
            int row_offset = 0, column_offset = 0;
            // function takes user input on how the rain should effect the map 
            rain_on_map(row_spacing, column_spacing, row_offset, column_offset, map); 
            print_map(map, starting_lives, money); 
        }
    }
                  
    printf("\nGame Over!\n"); 
}

////////////////////////////////////////////////////////////////////////////////
/////////////////////////////  YOUR FUNCTIONS //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// TODO: Put your functions here

// function checks if the enemy input is valid so it can be added to starting point.
void check_valid_enemy_input(int enemies, int start_row, int start_col, 
    int starting_lives, int money, struct tile map[MAP_ROWS][MAP_COLUMNS]) {
    if (enemies > 0) {
        map[start_row][start_col].entity = ENEMY;
        map[start_row][start_col].n_enemies = enemies;
    } else if (enemies <= 0) {
        map[start_row][start_col].land = PATH_START;
    }
    print_map(map, starting_lives, money);
}

// function checks if the lake coordinates are valid and prints it onto map
void print_lake (int lake_row, int lake_col, int lake_height, int lake_width,
    int starting_lives, int money, struct tile map[MAP_ROWS][MAP_COLUMNS]) {
    if ((lake_row > MAP_ROWS || lake_col > MAP_COLUMNS) || (lake_row + lake_height 
        > MAP_ROWS || lake_col + lake_width > MAP_COLUMNS) || 
            (lake_row < 0 || lake_col < 0)) {
        printf("Error: Lake out of bounds, ignoring...\n");
        print_map(map, starting_lives, money);
    } else {
        for (int i = lake_row; i < lake_row + lake_height; i++) {
            for (int j = lake_col; j < lake_col + lake_width; j++)
            if (lake_row + lake_height <= MAP_ROWS && lake_col + lake_width <= 
                MAP_COLUMNS) {
                map[i][j].land = WATER;
            }
        }
        print_map(map, starting_lives, money);
    }
}

// function enables user to navigate from starting point to end point.
void find_end_point(int lake_row, int lake_col, int start_row, int start_col,
        int starting_lives, int money, struct tile map[MAP_ROWS][MAP_COLUMNS]) {
    char directions = 0;
    int path_row;
    int path_col;

    path_row = start_row;
    path_col = start_col;

    printf("Enter Path: ");

    while (map[path_row][path_col].land != PATH_END && scanf(" %c", &directions) 
        == 1) {
        if (directions == 'u') {
            map[path_row][path_col].land = PATH_UP;
            path_row--;
            if (path_row == lake_row && lake_col == path_col) {
                map[lake_row][lake_col].land = PATH_UP;
            }

        } else if (directions == 'd') {
            map[path_row][path_col].land = PATH_DOWN;
            path_row++;
            if (path_row == lake_row && lake_col == path_col) {
                map[lake_row][lake_col].land = PATH_DOWN;
            }

        } else if (directions == 'r') {
            map[path_row][path_col].land = PATH_RIGHT;
            path_col++;
            if (path_row == lake_row && lake_col == path_col) {
                map[lake_row][lake_col].land = PATH_RIGHT;
            }

        } else if (directions == 'l') {
            map[path_row][path_col].land = PATH_LEFT;
            path_col--;
            if (path_row == lake_row && lake_col == path_col) {
                map[lake_row][lake_col].land = PATH_LEFT;
            }
        }
    } 
    print_map(map, starting_lives, money);
}

// function allows user to spawn as many enemies onto map at starting point.
void spawn_enemies (int num_enemies, int start_row, 
        int start_col, struct tile map[MAP_ROWS][MAP_COLUMNS]) {
    scanf("%d", &num_enemies);
    int total_enemies = map[start_row][start_col].n_enemies + num_enemies;
    if (total_enemies > 0) {
        map[start_row][start_col].entity = ENEMY; 
        map[start_row][start_col].n_enemies = total_enemies;
    }
    
}

// function allows user to summon a basic tower at any coordinate on the map 
// if user has enough money and coordinates are inside the map.
int add_basic_tower (int tower_row, int tower_col, int money, 
    struct tile map[MAP_ROWS][MAP_COLUMNS]) {
    scanf("%d %d", &tower_row, &tower_col); 
    if (money >= 200 && tower_row < MAP_ROWS && tower_col < MAP_COLUMNS 
        && map[tower_row][tower_col].entity == EMPTY && 
            map[tower_row][tower_col].land == GRASS) {
        map[tower_row][tower_col].entity = BASIC_TOWER; 
        money -= 200;
        printf("Tower successfully created!\n");
    } else {
        printf("Error: Tower creation unsuccessful. Make sure you have at least"
            " $200 and that the tower is placed on a grass block with no entity.\n"); 
    }
    return money;
}

// function allows user to upgrade any basic tower TWICE if user has 
// enough money and checks validity of upgrade coordinates. 
int tower_upgrade (int upgrade_row, int upgrade_col, int money, 
    struct tile map[MAP_ROWS][MAP_COLUMNS]) {
    scanf("%d %d", &upgrade_row, &upgrade_col); 
    if (money >= 300 && map[upgrade_row][upgrade_col].entity == BASIC_TOWER) {
        map[upgrade_row][upgrade_col].entity = POWER_TOWER; 
        money -= 300;
        printf("Upgrade Successful!\n");
    } else if (money >= 500 && map[upgrade_row][upgrade_col].entity == POWER_TOWER) {
        map[upgrade_row][upgrade_col].entity = FORTIFIED_TOWER;
        money -= 500; 
        printf("Upgrade Successful!\n");
    } else if (upgrade_row < 0 || upgrade_row >= MAP_ROWS 
        || upgrade_col < 0 || upgrade_col >= MAP_COLUMNS) {
        printf("Error: Upgrade target is out-of-bounds.\n"); 
    } else if (map[upgrade_row][upgrade_col].entity != BASIC_TOWER && 
        map[upgrade_row][upgrade_col].entity != POWER_TOWER 
        && map[upgrade_row][upgrade_col].entity != FORTIFIED_TOWER) {
        printf("Error: Upgrade target contains no tower entity.\n");
    } else if (map[upgrade_row][upgrade_col].entity == FORTIFIED_TOWER) {
        printf("Error: Tower cannot be upgraded further.\n");
    } else if (map[upgrade_row][upgrade_col].entity == BASIC_TOWER && money < 300) {
        printf("Error: Insufficient Funds.\n"); 
    } else if (map[upgrade_row][upgrade_col].entity == POWER_TOWER && money < 500) {
        printf("Error: Insufficient Funds.\n");
    }
    return money; 
}

// function allows user to add rain in a desired pattern. 
void rain_on_map(int row_spacing, int column_spacing, int row_offset, int column_offset, 
    struct tile map[MAP_ROWS][MAP_COLUMNS]) {
    scanf("%d %d %d %d", &row_spacing, &column_spacing, &row_offset, &column_offset);
    row_offset = row_offset%row_spacing;
    if (row_offset < 0) row_offset = row_offset+row_spacing;

    column_offset = column_offset%column_spacing;
    if (column_offset < 0) column_offset = column_offset + column_spacing;

    for (int i = row_offset; i < MAP_ROWS; i += row_spacing) {
        for (int j = column_offset; j < MAP_COLUMNS; j += column_spacing) {
            if (map[i][j].entity == BASIC_TOWER || map[i][j].entity == POWER_TOWER) {
                map[i][j].entity = EMPTY;
                map[i][j].land = WATER;                 
            } else if (map[i][j].land == GRASS) {
                map[i][j].land = WATER;
            }
        }
    } 
} 
////////////////////////////////////////////////////////////////////////////////
/////////////////////////// PROVIDED FUNCTIONS  ///////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/**
 * Initialises map tiles to contain GRASS land and EMPTY entity.
 *
 * Parameters:
 *     map - The map to initialise.
 * Returns:
 *     Nothing.
 */
void initialise_map(struct tile map[MAP_ROWS][MAP_COLUMNS]) {
    for (int row = 0; row < MAP_ROWS; ++row) {
        for (int col = 0; col < MAP_COLUMNS; ++col) {
            map[row][col].land = GRASS;
            map[row][col].entity = EMPTY;
            map[row][col].n_enemies = 0;
        }
    }
}

/**
 * Prints all map tiles based on their value, with a header displaying lives
 * and money.
 *
 * Parameters:
 *     map   - The map to print tiles from.
 *     lives - The number of lives to print with the map.
 *     money - The amount of money to print with the map.
 * Returns:
 *     Nothing.
 */
void print_map(struct tile map[MAP_ROWS][MAP_COLUMNS], int lives, int money) {
    printf("\nLives: %d Money: $%d\n", lives, money);
    for (int row = 0; row < MAP_ROWS * 2; ++row) {
        for (int col = 0; col < MAP_COLUMNS; ++col) {
            print_tile(map[row / 2][col], row % 2);
        }
        printf("\n");
    }
}

/**
 * Prints either the land or entity component of a single tile, based on
 * the `land_print` parameter;
 *
 * Parameters:
 *     tile         - The tile to print the land/entity from
 *     land_print - Whether to print the land part of the tile or the entity
 *         part of the tile. If this value is 0, it prints the land, otherwise
 *         it prints the entity.
 * Returns:
 *     Nothing.
 */
void print_tile(struct tile tile, int land_print) {
    if (land_print) {
        if (tile.land == GRASS) {
            printf(" . ");
        } else if (tile.land == WATER) {
            printf(" ~ ");
        } else if (tile.land == PATH_START) {
            printf(" S ");
        } else if (tile.land == PATH_END) {
            printf(" E ");
        } else if (tile.land == PATH_UP) {
            printf(" ^ ");
        } else if (tile.land == PATH_RIGHT) {
            printf(" > ");
        } else if (tile.land == PATH_DOWN) {
            printf(" v ");
        } else if (tile.land == PATH_LEFT) {
            printf(" < ");
        } else if (tile.land == TELEPORTER) {
            printf("( )");
        } else {
            printf(" ? ");
        }
    } else {
        if (tile.entity == EMPTY) {
            printf("   ");
        } else if (tile.entity == ENEMY) {
            printf("%03d", tile.n_enemies);
        } else if (tile.entity == BASIC_TOWER) {
            printf("[B]");
        } else if (tile.entity == POWER_TOWER) {
            printf("[P]");
        } else if (tile.entity == FORTIFIED_TOWER) {
            printf("[F]");
        } else {
            printf(" ? ");
        }
    }
}