#include <iostream>
#include "tape_utils.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "yadro <input.txt> <output.txt>" << std::endl;
        return 0;
    }

    std::string input_file(argv[1]);
    std::string output_file(argv[2]);

    tape_impl t = read_tape_from_file(input_file);
    auto res = sort(t);
    write_tape_to_file(res, output_file);

    return 0;
}
