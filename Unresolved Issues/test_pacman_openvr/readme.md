temp/CMakeLists.txt：
    $ pacman -S ucrt64/mingw-w64-ucrt-x86_64-openvr
    $ pacman -Ql mingw-w64-ucrt-x86_64-openvr
        mingw-w64-ucrt-x86_64-openvr /ucrt64/
        mingw-w64-ucrt-x86_64-openvr /ucrt64/bin/
        mingw-w64-ucrt-x86_64-openvr /ucrt64/bin/libopenvr_api.dll
        mingw-w64-ucrt-x86_64-openvr /ucrt64/include/
        mingw-w64-ucrt-x86_64-openvr /ucrt64/include/openvr.h
        mingw-w64-ucrt-x86_64-openvr /ucrt64/include/openvr/
        mingw-w64-ucrt-x86_64-openvr /ucrt64/include/openvr/openvr.h
        mingw-w64-ucrt-x86_64-openvr /ucrt64/include/openvr/openvr_capi.h
        mingw-w64-ucrt-x86_64-openvr /ucrt64/include/openvr/openvr_driver.h
        mingw-w64-ucrt-x86_64-openvr /ucrt64/include/openvr/openvr_mingw.hpp
        mingw-w64-ucrt-x86_64-openvr /ucrt64/include/openvr_capi.h
        mingw-w64-ucrt-x86_64-openvr /ucrt64/include/openvr_driver.h
        mingw-w64-ucrt-x86_64-openvr /ucrt64/include/openvr_mingw.hpp
        mingw-w64-ucrt-x86_64-openvr /ucrt64/lib/
        mingw-w64-ucrt-x86_64-openvr /ucrt64/lib/libopenvr_api.a
        mingw-w64-ucrt-x86_64-openvr /ucrt64/lib/libopenvr_api.dll.a
        mingw-w64-ucrt-x86_64-openvr /ucrt64/share/
        mingw-w64-ucrt-x86_64-openvr /ucrt64/share/licenses/
        mingw-w64-ucrt-x86_64-openvr /ucrt64/share/licenses/openvr/
        mingw-w64-ucrt-x86_64-openvr /ucrt64/share/licenses/openvr/LICENSE
        mingw-w64-ucrt-x86_64-openvr /ucrt64/share/pkgconfig/
        mingw-w64-ucrt-x86_64-openvr /ucrt64/share/pkgconfig/openvr.pc
    $ cmake -S . -B build -G "Unix Makefiles" -DCMAKE_INSTALL_PREFIX=./install
    $ cmake --build build --config Release
    $ cmake --install build --config Release
    编译没问题，但steamvr无法正确处理这个驱动

