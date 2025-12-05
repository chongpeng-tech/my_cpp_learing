#include "Q3_Count_Islands.h"
#include <iostream> // 引入iostream，用于打印

int count_islands(const std::vector<std::vector<int>>& grid) {
    // 1. 解决 [Werror=unused-parameter] 错误：
    // 打印 grid 的尺寸，确保使用了参数
    if (grid.empty()) {
        // 如果为空，返回 0 (符合作业要求)
        return 0;
    }

    // 2. 避免 error: expected size ‘<int>’ 错误，确保函数返回一个int值
    // 这里只是为了让编译通过并运行测试，实际算法还没写

    // 打印第一行的尺寸，确保参数被使用 (这行代码只是临时的，为了绕过警告)
    std::cout << "Grid size: " << grid.size() << "x" << grid[0].size() << std::endl;

    // 暂时返回 0，让测试失败，但代码能运行
    return 0; 
}
