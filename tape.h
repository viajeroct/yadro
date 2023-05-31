#ifndef YADRO_TAPE_H
#define YADRO_TAPE_H

#include <cstdint>
#include <vector>

class tape {
public:
    using type = int32_t;
    using ctype = int32_t const;

    [[nodiscard]] virtual type read() const = 0;

    virtual void write(ctype &el) = 0;

    virtual void move_left() = 0;

    virtual void move_right() = 0;

    virtual void move_right_without_expand() = 0;

    virtual bool is_end() = 0;

    virtual std::vector<type> read_all_tape() = 0;
};

#endif
