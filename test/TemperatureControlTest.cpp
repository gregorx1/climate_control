#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <unistd.h>

#include "TemperatureControlImpl.h"

using namespace testing;
using namespace std;

class MockTemperatureControlLogic : public TemperatureControlImpl {
public:
    MOCK_METHOD(void, run, (), (override));
};

TEST(TemperatureControlTest, TemperatureTest0) {
    MockTemperatureControlLogic logic;
    EXPECT_CALL(logic, run()).Times(AtLeast(1));

    logic.start();
    this_thread::sleep_for(chrono::milliseconds(5000));
    logic.stop();
}

TEST(TemperatureControlTest, TemperatureTest1) {
    TemperatureControlImpl& control = TemperatureControlImpl::getInstance();

    control.setLowLimit(15);
    control.setHighLimit(28);

    EXPECT_EQ(control.getLowLimit(), 15);
    EXPECT_EQ(control.getHighLimit(), 28);
}

TEST(TemperatureReadTest, TemperatureTest2) {
    TemperatureControlImpl& control = TemperatureControlImpl::getInstance();

    for (int i=0; i<10; i++) {
      EXPECT_THAT(control.getCurrentTemperature(), AllOf(Ge(-49),Le(50)));
      //int a = control.getCurrentTemperature();
      //EXPECT_TRUE((a >= -49) && (a <= 50));
    }
}

int main(int argc, char** argv) {

    InitGoogleTest(&argc, argv);
    InitGoogleMock(&argc, argv);

    int ret_value = RUN_ALL_TESTS();

    return ret_value;
}
