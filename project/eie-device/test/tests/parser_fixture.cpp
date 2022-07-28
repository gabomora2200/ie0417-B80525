#include "gtest/gtest.h"

#include <eie_device/eie_device.h>
#include <testutil/rand_gen.hpp>
#include <eie_device/parser/parser.h>


/** Example fixture class for demo API tests */
class parser_fixture : public testing::Test
{
 protected:
    /* Fixture class members, accesible from test functions */
    int value;
    testutil::rand_gen rng;

    /* Fixture class constructor */
    /* NOTE: Using reproducible random value for seed, check
     * explanation in unittest_main.cpp for more details */
    parser_fixture()
        : value(2), rng(rand())
    {
        std::cout << "parser Test fixture constructor! "<< std::endl;
        std::cout << "  RNG seed " << rng.get_seed() << std::endl;
    }

    virtual void SetUp() {
        std::cout << "parser Test fixture SetUp! "<< std::endl;
        srand(rng.get_seed());
    }

    virtual void TearDown() {
        std::cout << "Parser Test fixture TearDown! \n"<< std::endl;
    }
};

/** Test the functions create and destroy of command runner using a fixture */
TEST_F(parser_fixture, callback_resp_parser_test)
{ 
    char *payload = "{\"topic\":\"sensor/0/things/twin/events/modified\",\"headers\":{\"authorization\":\"Basic ZGl0dG86ZGl0dG8=\",\"x-real-ip\":\"172.18.0.1\",\"x-forwarded-user\":\"ditto\",\"x-ditto-pre-authenticated\":\"nginx:ditto\",\"postman-token\":\"bd030713-70dc-48b3-a59d-baac446ac4fb\",\"host\":\"localhost:8080\",\"x-forwarded-for\":\"172.18.0.1\",\"accept-encoding\":\"gzip, deflate, br\",\"accept\":\"/\",\"user-agent\":\"PostmanRuntime/7.29.2\",\"ditto-originator\":\"nginx:ditto\",\"response-required\":false,\"version\":2,\"requested-acks\":[],\"content-type\":\"application/json\",\"correlation-id\":\"28c41ecd-7178-4ca8-b32a-4d68b59d7c4d\"},\"path\":\"/features/ft_1/properties/configuration\",\"value\":{\"value\":false},\"revision\":66,\"timestamp\":\"2022-07-27T05:15:13.274597013Z\"}";
    char thing_id[100];
    char feature_id[100];
    char data[100]; 
    callback_resp_parser(payload, thing_id, feature_id, data);
}