#ifndef YADRO_TAPE_UTILS_H
#define YADRO_TAPE_UTILS_H

#include "tape_impl.h"
#include <random>

namespace tape_utils {
    static const std::string config_file_name = "../config";
    static const std::string data_path = "../data/";
    static const std::string tmp_dir = "../data/";

    static std::mt19937 gen(time(nullptr)); // NOLINT
    static std::uniform_int_distribution<int> distrib(1, 100);

    void write_tape_to_file(tape &t, std::string const &file);

    tape_impl read_tape_from_file(std::string const &file);

    std::vector<std::string> split_into_tapes(tape &t, int tmp_tape_size);

    void clear_tmp_files(std::vector<std::string> const &temp_tapes_names);

    void sort_each_tape(std::vector<std::string> const &temp_tapes_names);

    tape_impl merge_tapes(std::vector<std::string> const &temp_tapes_names);

    auto generate_random_tape();

    tape_impl sort(tape &t);
}

#endif
