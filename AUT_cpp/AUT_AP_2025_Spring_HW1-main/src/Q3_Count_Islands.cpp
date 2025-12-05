#include "Q3_Count_Islands.h"
#include <iostream> // 引入iostream，用于打印
void dfs_sink(std::vector<std::vector<int>>& grid_copy, int r, int c);
int count_islands(const std::vector<std::vector<int>>& grid) {
    if(grid.empty() || grid[0].empty()){
        return 0;
    }
    int count_island = 0;
    std::vector<std::vector<int>> grid_copy = grid;
    //复制一份，方便修改
    for(std::size_t row = 0; row < grid_copy.size(); row++){
        for(std:: size_t column = 0; column < grid_copy[row].size(); column++){
            if(grid_copy[row][column] == 1){
                count_island++;
                dfs_sink(grid_copy, row, column);
            }else{
                continue;
            }
        }
    }
    return count_island;
}
    void dfs_sink(std::vector<std::vector<int>>& grid_copy, int r, int c){
        int R = grid_copy.size();
        int C = grid_copy[0].size();
        if(r < 0 || r >= R || c < 0 || c >= C || grid_copy[r][c] == 0){
            return;
        }else{
            grid_copy[r][c] = 0;
            dfs_sink(grid_copy, r - 1, c);
            dfs_sink(grid_copy, r + 1, c);
            dfs_sink(grid_copy, r, c - 1);
            dfs_sink(grid_copy, r, c + 1);
        }
    }
