./CMakeLists.txt：
    $ pacman -S ucrt64/mingw-w64-ucrt-x86_64-spdlog
    $ cmake -S . -B build -G "Unix Makefiles" -DCMAKE_INSTALL_PREFIX=./install
    $ cmake --build build --config Release
    $ cmake --install build --config Release

    msvc编译的openvr驱动，能被steamvr正确加载和运行，表现在：
        1. hmd的screen发白（被steamvr抓取到了）
        2. screen显示steamvr的定位场景（远处是山脉，地面是一个类似蛛网的东西）
        3. 显示steamvr home
    但gcc编译的openvr驱动，能被steamvr加载，但运行时出错，表现在：
        1. hmd的screen没反应
        2. rotation.log中正常看到了日志在更新，但从网页控制台中可见发生了错误：Exception c0000005（可能是说错误访问了内存位置）
        3. 报错后，steamvr就退出了该驱动，然后切换到其他驱动了

