#ifndef YADRO_TAPE_H
#define YADRO_TAPE_H

#include <cstdint>

class tape {
public:
    using type = int32_t;
    using ctype = int32_t const;

    virtual type read() = 0;

    virtual void write(ctype &el) = 0;

    virtual void move_left() = 0;

    virtual void move_right() = 0;
};

#endif
