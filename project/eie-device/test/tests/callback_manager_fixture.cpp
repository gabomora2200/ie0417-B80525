#include "gtest/gtest.h"

#include <eie_device/eie_device.h>
#include <eie_device/callback_manager/callback_manager.h>
#include <eie_device/callback_manager/callback.h>
#include <testutil/rand_gen.hpp>


// Creando mock functions
void mock_callback_fn(char* payload, int payloadlen){
    std::cout << payload << std::endl;
}

/** Example fixture class for demo API tests */
class callback_manager_fixture : public testing::Test
{
 protected:
    /* Fixture class members, accesible from test functions */
    int value;
    testutil::rand_gen rng;
    callback_manager *clbk_mgr;

    /* Fixture class constructor */
    /* NOTE: Using reproducible random value for seed, check
     * explanation in unittest_main.cpp for more details */
    callback_manager_fixture()
        : value(2), rng(rand())
    {
        std::cout << "Test fixture constructor! "<< std::endl;
        std::cout << "  RNG seed " << rng.get_seed() << std::endl;
    }

    virtual void SetUp() {
        std::cout << "Test fixture SetUp! "<< std::endl;
        srand(rng.get_seed());
        clbk_mgr = callback_manager_create();
        ASSERT_NE(clbk_mgr, nullptr);
        /* NOTE: Both the constructor and SetUp methods are called for each test.
         * Check Googletest FAQ for more details on when to use each one:
         * https://github.com/google/googletest/blob/main/docs/faq.md#should-i-use-the-constructordestructor-of-the-test-fixture-or-setupteardown-ctorvssetup */
    }

    virtual void TearDown() {
        std::cout << "Test fixture TearDown! "<< std::endl;
        callback_manager_destroy(clbk_mgr);
        /* NOTE: Both the destructor and TearDown methods are called for each test.
         * Check Googletest FAQ for more details on when to use each one:
         * https://github.com/google/googletest/blob/main/docs/faq.md#should-i-use-the-constructordestructor-of-the-test-fixture-or-setupteardown-ctorvssetup */
    }
};

/** Test the functions create and destroy of command runner using a fixture */
TEST_F(callback_manager_fixture, add_callback)
{
    int ret; 
    char ftID[] = "ft-1";
    eie_callback_execute_t clbkfn = (eie_callback_execute_t)mock_callback_fn;
    ret = callback_manager_add_clbk(clbk_mgr, ftID, clbkfn);
    ASSERT_EQ(ret, 0);
}

TEST_F(callback_manager_fixture, execute_callback)
{
    //Registering callback
    int ret; 
    char ftID[] = "ft-1";
    eie_callback_execute_t clbkfn = (eie_callback_execute_t)mock_callback_fn;
    ret = callback_manager_add_clbk(clbk_mgr, ftID, clbkfn);
    ASSERT_EQ(ret, 0);

    // Executing callback 
    char payload[6] = "HOLIS";
    int payloadlen = 6;
    ret = callback_manager_clbk_execute(clbk_mgr, ftID, payload, payloadlen);
    ASSERT_EQ(ret, 0);
}

TEST_F(callback_manager_fixture, execute_without_callback_register)
{
    // Executing callback 
    int ret; 
    char ftID[] = "ft-1";
    char payload[6] = "HOLIS";
    int payloadlen = 6;
    ret = callback_manager_clbk_execute(clbk_mgr, ftID, payload, payloadlen);
    ASSERT_EQ(ret, 1);
}

TEST_F(callback_manager_fixture, re_registering_callback)
{
    //Registering callback
    int ret; 
    char ftID[] = "ft-1";
    eie_callback_execute_t clbkfn = (eie_callback_execute_t)mock_callback_fn;
    ret = callback_manager_add_clbk(clbk_mgr, ftID, clbkfn);
    ASSERT_EQ(ret, 0);

    //Re-registration
    ret = callback_manager_add_clbk(clbk_mgr, ftID, clbkfn);
    ASSERT_EQ(ret, 1);
}



TEST_F(callback_manager_fixture, deleting_callback)
{
    //Registering callback
    int ret; 
    char ftID[] = "ft-1";
    eie_callback_execute_t clbkfn = (eie_callback_execute_t)mock_callback_fn;
    ret = callback_manager_add_clbk(clbk_mgr, ftID, clbkfn);
    ASSERT_EQ(ret, 0);

    //Deleting callback
    ret = callback_manager_delete_clbk_feature(clbk_mgr, ftID);
    ASSERT_EQ(ret, 0);

    // Executing callback 
    char payload[6] = "HOLIS";
    int payloadlen = 6;
    ret = callback_manager_clbk_execute(clbk_mgr, ftID, payload, payloadlen);
    ASSERT_EQ(ret, 1);
}