#include "gtest/gtest.h"

#include <sensor_commands/command_runner.h>
#include <testutil/rand_gen.hpp>

/** Example fixture class for demo API tests */
class command_runner_fixture : public testing::Test
{
 protected:
    /* Fixture class members, accesible from test functions */
    int value;
    testutil::rand_gen rng;

    /* Fixture class constructor */
    /* NOTE: Using reproducible random value for seed, check
     * explanation in unittest_main.cpp for more details */
    command_runner_fixture()
        : value(2), rng(rand())
    {
        std::cout << "Test fixture constructor! "<< std::endl;
        std::cout << "  RNG seed " << rng.get_seed() << std::endl;
    }

    virtual void SetUp() {
        std::cout << "Test fixture SetUp! "<< std::endl;
        srand(rng.get_seed());
        struct CommandRunnerConfig cmd_runner_cfg = {
            .q_max_size = (rand() % 999 + 1),
        };
        struct CommandRunner *cmd_runner = command_runner_create(&cmd_runner_cfg);
        /* NOTE: Both the constructor and SetUp methods are called for each test.
         * Check Googletest FAQ for more details on when to use each one:
         * https://github.com/google/googletest/blob/main/docs/faq.md#should-i-use-the-constructordestructor-of-the-test-fixture-or-setupteardown-ctorvssetup */
    }

    virtual void TearDown() {
        std::cout << "Test fixture TearDown! "<< std::endl;
        command_runner_destroy(cmd_runner);
        /* NOTE: Both the destructor and TearDown methods are called for each test.
         * Check Googletest FAQ for more details on when to use each one:
         * https://github.com/google/googletest/blob/main/docs/faq.md#should-i-use-the-constructordestructor-of-the-test-fixture-or-setupteardown-ctorvssetup */
    }
};

/** Test the functions create and destroy of command runner using a fixture */
TEST_F(command_runner_fixture, create_destroy)
{
    //int ret = 0;
    //int out = 0;
    struct CommandRunnerConfig *cfg = nullptr;
    struct CommandRunner *cmd_runner_test = command_runner_create(cfg);
    int destroy = command_runner_destroy(cmd_runner_test)

    //std::cout << "  Num A: " << num_a << std::endl;
    //std::cout << "  Num B: " << num_b << std::endl;

    //ret = demo_api_add(num_a + value, num_b, &out);
    ASSERT_EQ(cmd_runner, nullptr);
    ASSERT_EQ(destroy, -1);
}

/** Test the functions start and stop of command runner using a fixture */
TEST_F(command_runner_fixture, start_stop)
{
    //std::cout << "  Num A: " << num_a << std::endl;
    //std::cout << "  Num B: " << num_b << std::endl;
    int ret_1 = command_runner_start(nullptr);
    int ret_2 = command_runner_start(cmd_runner);
    int ret_3 = command_runner_stop(nullptr);
    int ret_4 = command_runner_stop(cmd_runner);
    //ret = demo_api_mult(num_a, num_b + value, &out);
    ASSERT_EQ(ret_1, -1);
    ASSERT_EQ(ret_2, 0);
    ASSERT_EQ(ret_3, -1);
    ASSERT_EQ(ret_4, 0);
}

/** Test the function send command of command runner using a fixture */
TEST_F(command_runner_fixture, command_send_single)
{
    struct Command *msg_cmd = msg_command_create("Test de prueba\n");
    
    //int ret_1 = command_runner_start(nullptr);
    int ret_1 = command_runner_start(cmd_runner);
    int ret_2 = command_runner_send(nullptr, msg_cmd);
    int ret_3 = command_runner_send(cmd_runner, nullptr);
    int ret_4 = command_runner_send(cmd_runner, msg_cmd);
    int ret_5 = command_runner_stop(cmd_runner);
    //ret = demo_api_mult(num_a, num_b + value, &out);
    ASSERT_EQ(ret_1, 0);
    ASSERT_EQ(ret_2, -1);
    ASSERT_EQ(ret_3, -1);
    ASSERT_NE(ret_4, -1);
    ASSERT_EQ(ret_5, 0);
}
