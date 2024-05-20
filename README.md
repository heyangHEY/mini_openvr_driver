# mini_openvr_driver
### MSVC
```
cmake -S . -B build -G "Visual Studio 17 2022" -A x64 -DCMAKE_INSTALL_PREFIX=./install
cmake --build build --config Release
cmake --install build --config Release
```

### vrpath
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
