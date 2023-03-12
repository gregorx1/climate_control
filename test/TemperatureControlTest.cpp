//#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <unistd.h>

#include "TemperatureControlImpl.h"

using namespace testing;
using namespace std;

#if 0
class MockTemperatureControlLogic : public TemperatureControlImpl {
public:
    MOCK_METHOD(void, run, (), (override));
};

TEST(TemperatureControlTest, LogicTest) {
    TemperatureControlImpl& control = TemperatureControlImpl::getInstance();

    MockTemperatureControlLogic logic;
    EXPECT_CALL(logic, start()).Times(AtLeast(1));

    control.start();
    this_thread::sleep_for(chrono::milliseconds(1000));
    control.stop();
}
#endif

TEST(TemperatureControlTest, TemperatureTest1) {
    TemperatureControlImpl& control = TemperatureControlImpl::getInstance();

    control.setLowLimit(15);
    control.setHighLimit(28);

    EXPECT_EQ(control.getLowLimit(), 15);
    EXPECT_EQ(control.getHighLimit(), 28);
}

#if 1
TEST(TemperatureReadTest, TemperatureTest2) {
    TemperatureControlImpl& control = TemperatureControlImpl::getInstance();

    for (int i=0; i<10; i++) {
      //EXPECT_THAT(control.getCurrentTemperature(), AllOf(Ge(-49),Le(50)));
      int a = control.getCurrentTemperature();
      EXPECT_TRUE((a >= -49) && (a <= 50));
    }
}
#endif

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
