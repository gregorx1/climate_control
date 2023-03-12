#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <unistd.h>

#include "TemperatureControlImpl.h"

using namespace testing;
using namespace std;

TEST(TemperatureControlTest, TemperatureTest1) {
    TemperatureControlImpl& control = TemperatureControlImpl::getInstance();

    control.setLowLimit(22);
    control.setHighLimit(28);

    EXPECT_EQ(control.getLowLimit(), 22);
    EXPECT_EQ(control.getHighLimit(), 28);
}

TEST(TemperatureReadTest, TemperatureTest2) {
    TemperatureControlImpl& control = TemperatureControlImpl::getInstance();

    for (int i=0; i<10; i++) {
      EXPECT_THAT(control.getCurrentTemperature(), AllOf(Ge(-49),Le(50)));
    }
}

int main(int argc, char** argv) {
    TemperatureControlImpl& control = TemperatureControlImpl::getInstance();
    control.start();

    InitGoogleTest(&argc, argv);
    //InitGoogleMock(&argc, argv);

    int ret_value = RUN_ALL_TESTS();

    sleep(10);
    control.stop();

    return ret_value;
}
