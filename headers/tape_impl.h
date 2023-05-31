#ifndef YADRO_TAPE_IMPL_H
#define YADRO_TAPE_IMPL_H

#include "tape.h"
#include "tape_exception.h"
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

    [[nodiscard]] type read() const override {
        delay(cd.read_delay);
        return data[pos];
    }

    void write(ctype &el) override {
        delay(cd.write_delay);
        data[pos] = el;
    }

    bool is_end() override {
        return pos >= data.size();
    }

    void move_left() override {
        delay(cd.move_delay);
        if (pos == 0) data.push_front({});
        else pos--;
    }

    void move_right() override {
        if (pos + 1 >= data.size()) {
            data.push_back({});
        }
        move_right_without_expand();
    }

    void move_right_without_expand() override {
        delay(cd.move_delay);
        pos++;
    }

    std::vector<type> read_all_tape() override {
        std::vector<int> ans{};
        while (!is_end()) {
            ans.emplace_back(read());
            move_right_without_expand();
        }
        return ans;
    }

private:
    void read_config() {
        std::ifstream in(config);
        if (!in.is_open()) {
            throw tape_exception("Can't open config file");
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
