#ifndef YADRO_TAPE_UTILS_H
#define YADRO_TAPE_UTILS_H

#include "tape_impl.h"

tape_impl read_tape_from_file(std::string const &file);

void write_tape_to_file(tape_impl &t, std::string const &file);

tape_impl sort(tape_impl &t);

#endif
