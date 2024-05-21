#include "logger.hpp"
#include <thread>

void func()
{
    int num = 0;
    while(1)
    {
        LOG_T("This is a trace message, from func(), {}", num);
        LOG_D("This is a debug message, from func(), {}", num);
        LOG_I("This is an info message, from func(), {}", num);
        LOG_W("This is a warn message, from func(), {}", num);
        LOG_E("This is an error message, from func(), {}", num);
        LOG_C("This is a critical message, from func(), {}", num); 
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        num++;
    }
}

int main()
{
    build_logger("logger", "debug", "D:/workspace/mini_openvr_driver/logs/rotation.log");

    LOG_T("This is a trace message, from main()");
    LOG_T("这是一个 trace 级别的消息, from main()");
    LOG_D("This is a debug message, from main()");
    LOG_D("这是一个 debug 级别的消息, from main()");
    LOG_I("This is an info message, from main()");
    LOG_I("这是一个 info 级别的消息, from main()");
    LOG_W("This is a warn message, from main()");
    LOG_W("这是一个 warn 级别的消息, from main()");
    LOG_E("This is an error message, from main()");
    LOG_E("这是一个 error 级别的消息, from main()");
    LOG_C("This is a critical message, from main()");
    LOG_C("这是一个 critical 级别的消息, from main()");

    func();

    return 0;
}