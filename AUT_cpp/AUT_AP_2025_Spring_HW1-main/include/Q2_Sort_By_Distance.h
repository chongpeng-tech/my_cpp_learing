#ifndef Q2_SORT_BY_DISTANCE_H
#define Q2_SORT_BY_DISTANCE_H
//这两句是标签页，防止多个cpp文件反复引用导致反复编译
#include<vector>
#include<array>
//相当于.h文件里引用.h文件？
void sort_points_by_distance(std::vector<std::array<double, 3>>& points);

#endif //结束了