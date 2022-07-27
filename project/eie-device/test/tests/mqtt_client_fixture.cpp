#include "gtest/gtest.h"
#include "MQTTClient.h"
#include "time.h"

#include <eie_device/eie_device.h>
#include <eie_device/callback_manager/callback_manager.h>
#include <eie_device/callback_manager/callback.h>
#include <testutil/rand_gen.hpp>
#include <eie_device/mqtt_client/mqtt_client.h>

/** Example fixture class for demo API tests */
class mqtt_client_fixture : public testing::Test
{
 protected:
    /* Fixture class members, accesible from test functions */
    int value;
    testutil::rand_gen rng;
    callback_manager *clbk_mgr;
    MQTTClient *mqtt_client;

    /* Fixture class constructor */
    /* NOTE: Using reproducible random value for seed, check
     * explanation in unittest_main.cpp for more details */
    mqtt_client_fixture()
        : value(2), rng(rand())
    {
        std::cout << "MQTT CLIENT Test fixture constructor! "<< std::endl;
        std::cout << "  RNG seed " << rng.get_seed() << std::endl;
    }

    virtual void SetUp() {
        std::cout << "MQTT CLIENT Test fixture SetUp! "<< std::endl;
        srand(rng.get_seed());
        clbk_mgr = callback_manager_create();
        ASSERT_NE(clbk_mgr, nullptr);
        char corr_id[] = "1234";
        char thing_id[] = "sensor:0";
        mqtt_client = MQTT_client_create(clbk_mgr, corr_id, thing_id);
        ASSERT_NE(mqtt_client, nullptr);
    }

    virtual void TearDown() {
        std::cout << "MQTT CLIENT Test fixture TearDown! \n"<< std::endl;
        MQTT_client_destroy(mqtt_client);
        callback_manager_destroy(clbk_mgr);
    }
};

/** Test the functions create and destroy of command runner using a fixture */
TEST_F(mqtt_client_fixture, valid_publish)
{
    int ret; 
    char topic[] = "eie-manager/sensor:0";
    char message[] = "{\"topic\":\"/sensor:0/things/twin/commands/modify\",\"path\":\"/features/ft_1/properties/status\",\"value\":{\"value\":9}}";
    ret = MQTT_publish(mqtt_client, topic, message);
    ASSERT_EQ(ret, 1);
}

TEST_F(mqtt_client_fixture, invalid_publish)
{
    int ret; 
    char message[] = "eie-device/Test Publish";
    ret = MQTT_publish(mqtt_client, NULL, message);
    ASSERT_EQ(ret, 0);
}

TEST_F(mqtt_client_fixture, valid_subscribe)
{
    int ret; 
    char topic[] = "eie-manager/sensor:0";
    ret = MQTT_subscribe(mqtt_client, topic);
    ASSERT_EQ(ret, 1);
}

TEST_F(mqtt_client_fixture, invalid_subscribe)
{
    int ret; 
    ret = MQTT_subscribe(mqtt_client, NULL);
    ASSERT_EQ(ret, 0);
}