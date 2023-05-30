#include "tape_utils.h"
#include <string>
#include <iostream>

const std::string config_file_name = "../config";

void write_tape_to_file(tape_impl &t, std::string const &file) {
    std::ofstream out(file);
    auto res = t.read_all_tape();
    for (auto el: res) {
        out << el << " ";
    }
    out << std::endl;
    out.close();
}

tape_impl read_tape_from_file(std::string const &file) {
    std::ifstream in(file);
    using type = tape::type;
    type x;
    std::vector<type> data;
    while (in >> x) {
        data.emplace_back(x);
    }
    in.close();
    return tape_impl(data, config_file_name);
}

std::vector<std::string> split_into_tapes(tape_impl &t, int tmp_tape_size) {
    std::string file_pattern = "../tmp/tmp_tape_";
    int file_number = 0;
    std::vector<std::string> temp_tapes_names;
    while (true) {
        std::vector<int> part;
        int cur = 0;
        while (true) {
            part.emplace_back(t.read());
            cur++;
            if (t.can_move_right()) {
                tape_impl tmp_tape{part, config_file_name};
                std::string cur_file = file_pattern + std::to_string(file_number);
                write_tape_to_file(tmp_tape, cur_file);
                temp_tapes_names.push_back(cur_file);
                return temp_tapes_names;
            }
            if (cur == tmp_tape_size) {
                t.move_right();
                break;
            }
            t.move_right();
        }
        tape_impl tmp_tape{part, config_file_name};
        std::string cur_file = file_pattern + std::to_string(file_number);
        write_tape_to_file(tmp_tape, cur_file);
        temp_tapes_names.push_back(cur_file);
        file_number++;
    }
}

void clear_tmp_files(std::vector<std::string> const &temp_tapes_names) {
    for (auto &file: temp_tapes_names) {
        system(("rm " + file).c_str());
    }
}

void sort_each_tape(std::vector<std::string> const &temp_tapes_names) {
    for (auto &file: temp_tapes_names) {
        auto cur_tape = read_tape_from_file(file);
        auto vec = cur_tape.read_all_tape();
        std::sort(vec.begin(), vec.end());
        auto sorted_tape = tape_impl{vec, config_file_name};
        write_tape_to_file(sorted_tape, file);
    }
}

tape_impl merge_tapes(std::vector<std::string> const &temp_tapes_names) {
    std::vector<tape_impl> tapes;
    for (auto &file: temp_tapes_names) {
        tapes.push_back(read_tape_from_file(file));
    }
    tape_impl ans{1, config_file_name};
    int total = 0;
    while (true) {
        auto mn = INT_MAX;
        auto pos = -1;
        for (int i = 0; i < tapes.size(); i++) {
            auto &t = tapes[i];
            if (!t.is_end()) {
                if (mn > t.read()) {
                    mn = t.read();
                    pos = i;
                }
            }
        }
        if (mn == INT_MAX) {
            break;
        }
        ans.move_right();
        ans.write(mn);
        tapes[pos].move_right_sp();
        total++;
    }
    total--;
    while (total--) {
        ans.move_left();
    }
    return ans;
}

auto generate_random_tape() {
    size_t sz = rand() % 100;
    tape_impl tape{sz, config_file_name};
    std::vector<int> data;
    for (int i = 0; i < sz; i++) {
        int value = rand() % 100;
        tape.write(value);
        data.push_back(value);
        tape.move_right_sp();
    }
    while (sz--) {
        tape.move_left();
    }
    write_tape_to_file(tape, "../input_data/input.txt");
    return data;
}

tape_impl sort(tape_impl &t) {
    auto ttn = split_into_tapes(t, 3);
    sort_each_tape(ttn);
    auto res = merge_tapes(ttn);
    clear_tmp_files(ttn);
    return {res};
}
