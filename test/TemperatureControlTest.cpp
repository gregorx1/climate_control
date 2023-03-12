#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <unistd.h>

#include "TemperatureControlImpl.h"

using namespace testing;
using namespace std;

TEST(TemperatureControlTest, TemperatureTest) {
    TemperatureControlImpl& control = TemperatureControlImpl::getInstance();

    control.setTemperature(25);
    EXPECT_EQ(control.getTemperature(), 25);

    control.setTemperature(30);
    EXPECT_EQ(control.getTemperature(), 30);
}

int main(int argc, char** argv) {
    TemperatureControlImpl& control = TemperatureControlImpl::getInstance();

    //control.start();
    //sleep(10);
    //InitGoogleMock(&argc, argv);
    InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
