#include"Q2_Sort_By_Distance.h"
#include<algorithm>

void sort_points_by_distance(std::vector<std::array<double, 3>>& points){
    std::sort(points.begin(), points.end(),
    [](const std::array<double, 3>& a,
    const std::array<double, 3>& b) -> bool{
            double a_distance = a[0]*a[0] + a[1]*a[1] + a[2]*a[2];
            double b_distance = b[0]*b[0] + b[1]*b[1] + b[2]*b[2];
            return a_distance < b_distance;
        }
    );
}