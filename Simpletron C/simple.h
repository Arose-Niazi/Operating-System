//
// Created by arose on 02/10/2020.
//

#ifndef simple_included
	#define simple_included
/*
    Input output operations constants.
*/
#define READ        10
#define WRITE       11

/*
    Load store operations constants.
*/
#define LOAD            20
#define STORE           21

/*
    Calculation operations constants.
*/
#define ADD             30
#define SUB             31
#define DIV             32
#define MUL             33

/*
    Control operations constants.
*/
#define BRANCH          40
#define BRANCHN         41
#define BRANCHZ         42
#define HALT            43

/*
    Customizable Settings
 */
#define END             -9999
#define IDENTIFIER_NAME "question mark"
#define IDENTIFIER      '?'
#define SIZE            100


void runSimpletron(const char filename[]);

#endif //Using this so multiple includes can be ignored.