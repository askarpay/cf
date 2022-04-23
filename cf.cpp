#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#define CELLS_SIZE 30000

void err(std::string errtxt) {
    std::cerr << "ERROR: " << errtxt << '\n';
}

void print_usage() {
    std::cout << "TODO: IMPLEMENT HELP MESSAGE" << '\n';
}

void log(std::string message) {
    // std::cout << "LOG: " << message << '\n';
}

int main(int argc, char const *argv[]) {
    // /* * * basic sanity checks * * */

    // // make sure an argument was given (presumably the file)
    // if (argc < 2) {
    //     err("no file specified to run.");
    //     return 1;
    // }

    // // try to grab the input file
    // std::ifstream srcfile(argv[1]);

    // if (!srcfile) {
    //     err("error reading file; make sure file exists.");
    //     // TODO: print help reference
    //     return 1;
    // }

    /* * * set up environment * * */

    // as per spec. 30k cells of possible values 0-255 all set to zero
    unsigned char cells[CELLS_SIZE] = {0};

    // points to address of first element of cells
    // cells is the same as &cells[0]
    unsigned char *pointer = cells;

    /* * * showtime * * */

    // descriptions referenced from http://brainfuck.org/brainfuck.html

    // hack for now, we'll deal with file input later
    char program[] = "++++.[->+<].";

    char command;

    // command_index keeps track of where we are in source code
    // note!!!!! we have TWO counters/pointers going on here. one lives in the
    // 30k array and one lives in the bf code that's being read in.
    for (int command_index = 0; command_index < std::strlen(program);
         command_index++) {
        command = program[command_index];

        switch (command) {
        /* The + command increments (increases by one) the value of the cell
         * indicated by the pointer. */
        case '+':
            (*pointer)++;
            log("incremented");
            break;

        /* The - command decrements (decreases by one) the value of the cell
         * indicated by the pointer. */
        case '-':
            (*pointer)--;
            log("decremented");
            break;

        /* The > command moves the pointer to the next cell to the right. */
        case '>':
            pointer++;
            log("move right");
            break;

        /* The < command moves the pointer to the next cell to the left. */
        case '<':
            pointer--;
            log("move left");
            break;

        /* The [ command checks the value of the cell indicated by the
         * pointer, and if its value is zero, control passes not to the next
         * command, but to the command following the matching ']' command. */
        case '[':
            // only trigger if cell value is 0, otherwise just move on
            if (*pointer == 0) {
                // we must be careful to not just move forward until the next
                // bracket becuase that destroys nested loops - we have to add
                // those to the count and then subtract their closing brackets
                // e.g.
                // [] -> 10
                // [[][]] -> 121210
                // [[][[]]] -> 12123210
                // [[[[[]]]]] -> 1234543210
                int count = 1;
                do {
                    command_index++; // move forward in source code
                    if (program[command_index] == '[') {
                        count++;
                    } else if (program[command_index] == ']') {
                        count--;
                    }
                } while (count > 0);

                command_index++; // move to following command

                log("left bracket");
            }

            break;

        /* The ] command checks the value of the cell indicated by the
         * pointer, and if its value is nonzero, control passes not to the next
         * command, but to the command following the matching '[' command. */
        case ']':
            // see above for logic explanation
            if (*pointer != 0) {
                int count = 1;
                do {
                    command_index--; // move backwards in source code
                    if (program[command_index] == ']') {
                        count++;
                    } else if (program[command_index] == '[') {
                        count--;
                    }
                } while (count > 0);

                command_index++; // move to following command

                log("right bracket");
            }

            break;

        /* The . command outputs the value of the cell indicated by the
         * pointer. */
        case '.':
            // std::cout << *pointer;
            std::cout << "int: " << (int)(*pointer) << '\n';
            log("print");
            break;

        /* The , command requests one byte of input, and sets the cell
         * indicated by the pointer to the value received, if any. */
        case ',':
            char input;
            std::cin >> input;
            *pointer = input;
            log("get input");
            break;

        default:
            // do nothing (ignore)
            break;
        }

        // FOR TESTING
        {
            std::cout << "command: " << command << '\n';
            for (int i = 0; i < 10; i++) {
                std::cout << (int)(cells[i]) << ' ';
            }
            std::cout << '\n' << '\n';
        }
    }

    return 0;
}