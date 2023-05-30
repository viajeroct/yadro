#ifndef YADRO_TAPE_IMPL_H
#define YADRO_TAPE_IMPL_H

#include "tape.h"
#include <deque>
#include <utility>
#include <thread>
#include <fstream>
#include <vector>

class tape_impl : public tape {
public:
    explicit tape_impl(size_t sz, std::string file_name) : config(std::move(file_name)) {
        read_config();
        data.resize(sz);
    }

    explicit tape_impl(std::vector<type> const &d, std::string file_name) :
            tape_impl(d.size(), std::move(file_name)) {
        std::copy(d.begin(), d.end(), data.begin());
    }

    explicit tape_impl(std::string file_name) : tape_impl(1, std::move(file_name)) {}

    type read() override {
        delay(cd.read_delay);
        return data[pos];
    }

    void write(ctype &el) override {
        delay(cd.write_delay);
        data[pos] = el;
    }

    bool can_move_right() {
        return pos + 1 >= data.size();
    }

    bool is_end() {
        return pos == data.size();
    }

    void move_left() override {
        delay(cd.move_delay);
        if (pos == 0) data.push_front({});
        else pos--;
    }

    void move_right() override {
        delay(cd.move_delay);
        if (pos + 1 == data.size()) {
            data.push_back({});
        }
        pos++;
    }

    void move_right_sp() {
        delay(cd.move_delay);
        pos++;
    }

    std::vector<type> read_all_tape() {
        std::vector<int> ans{};
        while (true) {
            ans.emplace_back(read());
            if (pos + 1 == data.size()) {
                break;
            }
            move_right();
        }
        return ans;
    }

private:
    void read_config() {
        std::ifstream in(config);
        if (!in.is_open()) {
            throw std::runtime_error("Can't open config file");
        }
        in >> cd.move_delay >> cd.read_delay >> cd.write_delay;
        in.close();
    }

    static void delay(int mills) {
        std::this_thread::sleep_for(std::chrono::milliseconds(mills));
    }

    struct config_data {
        int move_delay{};
        int write_delay{};
        int read_delay{};
    };

    std::string config;
    config_data cd{};
    std::deque<type> data{};
    size_t pos{};
};

#endif
