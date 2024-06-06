# mini_openvr_driver
### 编译
```
chmod +x build.sh
./build.sh Release
```

### MSVC
```
cmake -S . -B build -G "Visual Studio 17 2022" -A x64 -DCMAKE_INSTALL_PREFIX=./install
cmake --build build --config Release
cmake --install build --config Release
```

### vrpath, 将该openvr驱动添加到steamvr搜索路径中
C:\Users\xx\AppData\Local\openvr\openvrpaths.vrpath
add:
```
"external_drivers" : 
[
    "D:\\workspace\\mini_openvr_driver\\install\\mini"
]
```

### steamvr.vrsettings
C:\Program Files (x86)\Steam\config\steamvr.vrsettings
add:
```
"driver_mini" : {
    "blocked_by_safe_mode" : false
}
```

### TODO
将未解决的问题记录在 Unresolved Issues 下：
1. 在 win11、msys2、ucrt64、pacman 的环境下编译 openvr 驱动，并让 steamvr 正常加载和运行。

### 注意
如果在 windows 上打开工程，请将工程设置为 CRLF 格式，而不是 LF 格式，防止代码中的中文注释影响编译。
参考：Unresolved Issues\test_utf8_and_LF\readme.md
