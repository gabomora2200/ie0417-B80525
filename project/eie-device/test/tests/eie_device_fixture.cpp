#include "gtest/gtest.h"

#include <eie_device/eie_device.h>
#include <testutil/rand_gen.hpp>


// Creando mock functions
void mock_eie_callback_fn(char* payload, int payloadlen){
    std::cout << payload << std::endl;
}

/** Example fixture class for demo API tests */
class eie_device_fixture : public testing::Test
{
 protected:
    /* Fixture class members, accesible from test functions */
    int value;
    testutil::rand_gen rng;
    struct device * dev;

    /* Fixture class constructor */
    /* NOTE: Using reproducible random value for seed, check
     * explanation in unittest_main.cpp for more details */
    eie_device_fixture()
        : value(2), rng(rand())
    {
        std::cout << "EIE DEVICE Test fixture constructor! "<< std::endl;
        std::cout << "  RNG seed " << rng.get_seed() << std::endl;
    }

    virtual void SetUp() {
        std::cout << "EIE DEVICE Test fixture SetUp! "<< std::endl;
        char cfg_json[] = "{\"namespace\":\"sensor\",\"features\":{\"ft_1\":{\"properties\":{\"configuration\":{\"ON\":true},\"status\":{\"value\":0}}}}}";
        srand(rng.get_seed());
        dev = eie_device_create(cfg_json);
        ASSERT_NE(dev, nullptr);
    }

    virtual void TearDown() {
        std::cout << "EIE DEVICE Test fixture TearDown! \n"<< std::endl;
        eie_device_destroy(dev);
    }
};

/** Test the functions create and destroy of command runner using a fixture */
TEST_F(eie_device_fixture, eie_device_register_callback_test)
{
    eie_status ret = OK; 
    char ftID[] = "ft_1";
    eie_callback_execute_t clbkfn = (eie_callback_execute_t)mock_eie_callback_fn;
    ret = eie_device_register_callback(dev, ftID, clbkfn);
    ASSERT_EQ(ret, OK);
}

TEST_F(eie_device_fixture, eie_device_re_register_callback_test)
{
    eie_status ret; 
    char ftID[] = "ft_1";
    eie_callback_execute_t clbkfn = (eie_callback_execute_t)mock_eie_callback_fn;
    ret = eie_device_register_callback(dev, ftID, clbkfn);
    ASSERT_EQ(ret, OK);

    ret = eie_device_register_callback(dev, ftID, clbkfn);
    ASSERT_EQ(ret, ERROR);
}

TEST_F(eie_device_fixture, eie_device_update_feature_test)
{
    eie_status ret; 
    char ftID[] = "ft_1";
    char data_update[] = "{\"value\":9}";
    ret = eie_device_update_feature(dev, ftID, data_update);
    ASSERT_EQ(ret, OK);
}
