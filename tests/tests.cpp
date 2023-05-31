#define BOOST_TEST_MODULE Testing tape
#define BOOST_TEST_NO_MAIN
#define BOOST_TEST_ALTERNATIVE_INIT_API

#include <boost/test/included/unit_test.hpp>
#include "../tape_utils.h"
#include "../tape_utils.cpp"

BOOST_AUTO_TEST_SUITE(test_tape_impl)

    BOOST_AUTO_TEST_CASE(first_test) {
        tape_impl ti{tape_utils::config_file_name};
        BOOST_TEST(ti.read() == 0);
        ti.write(1);
        ti.move_left();
        ti.write(2);
        BOOST_TEST(ti.read() == 2);
        ti.move_right();
        ti.move_right();
        ti.move_right();
        ti.write(3);
        ti.move_right();
        ti.move_left();
        BOOST_TEST(ti.read() == 3);
        ti.move_left();
        ti.move_left();
        ti.move_left();
        tape_utils::write_tape_to_file(ti, "../tmp/output");
        auto res = tape_utils::read_tape_from_file("../tmp/output").read_all_tape();
        BOOST_TEST((res == std::vector<tape::type>{2, 1, 0, 3, 0}));
    }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(test_sorting_tape)

    BOOST_AUTO_TEST_CASE(first_test) {
        int tests = 3;
        for (int i = 0; i < tests; i++) {
            auto arr = tape_utils::generate_random_tape();
            auto tape = tape_utils::read_tape_from_file("../input_data/input.txt");
            auto sorted = tape_utils::sort(tape);
            auto my = sorted.read_all_tape();
            std::sort(arr.begin(), arr.end());
            BOOST_TEST(arr == my);
        }
    }

    BOOST_AUTO_TEST_CASE(test_sorting_small_tape) {
        auto tape = tape_impl({3, 2, 1}, tape_utils::config_file_name);
        auto res = tape_utils::sort(tape).read_all_tape();
        BOOST_TEST((res == std::vector<int>{1, 2, 3}));
    }

BOOST_AUTO_TEST_SUITE_END()

int main(int argc, char *argv[]) {
    return boost::unit_test::unit_test_main(init_unit_test, argc, argv);
}
