#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

void err(std::string errtxt) {
    std::cerr << "ERROR: " << errtxt << '\n';
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
    unsigned char cells[30000] = {0};
    // points to address of first element of cells
    // cells is the same as &cells[0]
    unsigned char *pointer = cells;

    /* * * showtime * * */

    // descriptions referenced from http://brainfuck.org/brainfuck.html

    // hack for now, deal with file input later
    // this program prints ascii value 51 or "3"
    char program[] =
        "++++++++++ ++++++++++ ++++++++++ ++++++++++ ++++++++++ + .";
    char command;

    for (unsigned int i = 0; i < std::strlen(program); i++) {
        command = program[i];

        switch (command) {
        /* The + command increments (increases by one) the value of the cell
         * indicated by the pointer. */
        case '+':
            (*pointer)++;
            break;

        /* The - command decrements (decreases by one) the value of the cell
         * indicated by the pointer. */
        case '-':
            (*pointer)--;
            break;

        /* The > command moves the pointer to the next cell to the right. */
        case '>':
            pointer++;
            break;

        /* The < command moves the pointer to the next cell to the left. */
        case '<':
            pointer--;
            break;

        /* The [ command checks the value of the cell indicated by the
         * pointer, and if its value is zero, control passes not to the next
         * command, but to the command following the matching ']' command. */
        case '[':
            /* NOTE: "The easy way to match brackets is to use a stack: when
             * a '[' is encountered, push its location on the stack; when a ']'
             * is encountered, pop the location of the matching '[' off the
             * stack. )"
             */

            /* TODO: IMPLEMENT */
            break;

        /* The ] command checks the value of the cell indicated by the
         * pointer, and if its value is nonzero, control passes not to the next
         * command, but to the command following the matching '[' command. */
        case ']':

            /* TODO: IMPLEMENT */
            break;
        /* The . command outputs the value of the cell indicated by the
         * pointer. */
        case '.':
            std::cout << *pointer;
            break;

        /* The , command requests one byte of input, and sets the cell
         * indicated by the pointer to the value received, if any. */
        case ',':
            char input;
            std::cin >> input;
            *pointer = input;
            break;
        default:
            // do nothing (ignore)
            break;
        }
    }

    return 0;
}