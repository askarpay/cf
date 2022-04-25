#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#define CELLS_SIZE 30000
const bool DEBUG = false;

void err(std::string errtxt) {
    std::cerr << "[ERROR] " << errtxt << '\n';
}

void print_usage() {
    std::cout << "USAGE: ./cf path/to/program.bf\n";
}

void log(std::string message) {
    if (DEBUG) {
        std::cout << "[LOG] " << message << '\n';
    }
}

int main(int argc, char const *argv[]) {
    // /* * * basic sanity checks * * */

    // make sure an argument was given (presumably the file)
    if (argc < 2) {
        err("no file specified to run.");
        print_usage();
        return 1;
    }

    // try to grab the input file
    std::ifstream srcfile(argv[1]);

    if (!srcfile) {
        err("error reading file; make sure file exists.");
        print_usage();
        return 1;
    }

    // set up program buffer, and stream the filestream into the buffer
    const int MAX_PROGRAM_SIZE = 65535;
    char program[MAX_PROGRAM_SIZE];
    srcfile.read(program, MAX_PROGRAM_SIZE);

    /* * * set up environment * * */

    // as per spec. 30k cells of possible values 0-255 all set to zero
    unsigned char cells[CELLS_SIZE] = {0};

    // points to address of first element of cells
    // cells is the same as &cells[0]
    unsigned char *pointer = cells;

    // declarations for the loop
    char command;
    int counter_for_left;
    int counter_for_right;

    /* * * showtime * * */

    // descriptions referenced from http://brainfuck.org/brainfuck.html

    // // hack for now, we'll deal with file input later
    // // sample program prints hello world :)
    // char program[] =
    //     ">++++++++[<+++++++++>-]<.>++++[<+++++++>-]<+.+++++++..+++.>>++++++[<++"
    //     "+++++>-]<++.-- -- -- -- -- --.>++ ++ ++[<++ ++ ++ ++ +> - ] < +.<.++
    //     "
    //     "+.-- -- --.-- -- -- --.>>>++ ++[<++ ++ ++ ++> - ] <+.";

    // command_index keeps track of where we are in source code
    // note!!!!! we have TWO counters/pointers going on here. one lives in
    // the 30k array and one lives in the bf code that's being read in.
    int command_index = 0;

    while (program[command_index] != '\0') {
        command = program[command_index];

        switch (command) {
        /* The + command increments (increases by one) the value of the
         * cell indicated by the pointer. */
        case '+':
            (*pointer)++;
            log("incremented");
            break;

        /* The - command decrements (decreases by one) the value of the
         * cell indicated by the pointer. */
        case '-':
            (*pointer)--;
            log("decremented");
            break;

        /* The > command moves the pointer to the next cell to the right.
         */
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
         * pointer, and if its value is zero, control passes not to the
         * next command, but to the command **following** the matching ']'
         * command. */
        case '[':
            // only trigger if cell value is 0, otherwise just move on
            if (*pointer == 0) {
                // we must be careful to not just move forward until the
                // next bracket becuase that destroys nested loops - we
                // have to add those to the count and then subtract their
                // closing brackets e.g.
                // [] -> 10
                // [[][]] -> 121210
                // [[][[]]] -> 12123210
                // [[[[[]]]]] -> 1234543210
                counter_for_left = 1;
                do {
                    command_index++; // step forward in source code
                    if (program[command_index] == '[') {
                        counter_for_left++;
                    } else if (program[command_index] == ']') {
                        counter_for_left--;
                    }
                } while (counter_for_left != 0);

                log("left bracket");
            }

            break;

        /* The ] command checks the value of the cell indicated by the
         * pointer, and if its value is nonzero, control passes not to the
         * next command, but to the command following the matching '['
         * command. */
        case ']':
            // to simplify it, we can just jump back to the previous left
            // bracket. if we're done looping that'll just send it back
            counter_for_right = 1;

            while (counter_for_right != 0) {
                command_index--; // move backwards in source code
                if (program[command_index] == ']') {
                    counter_for_right++;
                } else if (program[command_index] == '[') {
                    counter_for_right--;
                }
            }

            // at the end of each command process we call command_index++
            // this messes up the code above since we do need to evaluate the
            // [ that we land on. so we call command_index-- to undo it
            // this took a silly amount of time to fix (hours) - the final bit
            // of code i had to bang my head against to finish. now it works!!!

            /* here is a wizard keeping it safe. just for good measure

            ___ __ ._`.*.'_._ ____ ____
             . +  * .o   o.* `.`. +.    .
            *  . ' ' |\^/|  `. * .  * `
                      \V/ . +
                      /_\  .`.
            ======== _/ \_ =====::.*

            */

            command_index--;

            log("right bracket");
            break;

        /* The . command outputs the value of the cell indicated by the
         * pointer. */
        case '.':
            std::cout << *pointer;

            if (DEBUG) {
                // prints raw int. e.g. char 48 is '0' but 48 in int.
                // helpful for low values that are control character in ascii
                std::cout << '\n' << "int: " << (int)(*pointer) << '\n';
            }

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

        if (DEBUG) {
            std::cout << "command: " << command << '\n';
            for (int i = 0; i < 10; i++) {
                std::cout << (int)(cells[i]) << ' ';
            }
            std::cout << '\n' << '\n';

            getchar(); // press enter to step through
        }

        command_index++; // go to next command
    }

    std::cout << '\n'; // print final newline just to tidy things up

    return 0;
}