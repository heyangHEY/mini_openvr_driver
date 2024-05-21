如果在 windows 上打开工程，请将工程设置为 CRLF 格式，而不是 LF 格式，防止代码中的中文注释影响编译。

结论来自这样一个发现：
    src\logger.cpp 包含中文注释，编译正常，但 test_spdlog.exe 运行后直接崩溃（闪现）。但将文件编码格式从 UTF-8 改为 UTF-8 with BOM，或者将 LF 改为 CRLF 时，编译运行正常。

究其原因：
    logger 是个共享指针，logger.cpp:16 行的代码受到15行中文注释的影响，实际上没有被编译，导致 logger.cpp:24 行断言发现 logger.get() 是个空指针。
