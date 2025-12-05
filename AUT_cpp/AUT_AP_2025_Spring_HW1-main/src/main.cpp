#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <array>

#include "Q2_Sort_By_Distance.h"
#include "Q3_Count_Islands.h"

int main(int argc, char **argv) {
    // 核心修正：将 true 改为 false，激活单元测试
    if (false) 
    {
        // debug section (现在跳过)
    } else {
        // 解决终端无输出问题：强制 GTest 将结果输出到文件
        ::testing::GTEST_FLAG(output) = "xml:test_results.xml"; 

        ::testing::InitGoogleTest(&argc, argv);
        std::cout << "RUNNING TESTS ..." << std::endl; // 这行可能依然看不见

        int ret{RUN_ALL_TESTS()};

        if (!ret)
            std::cout << "<<<SUCCESS>>>" << std::endl;
        else
            std::cerr << "FAILED" << std::endl;

        // 返回 ret，如果所有测试通过，则 ret=0
        return ret; 
    }
    return 0;
}
