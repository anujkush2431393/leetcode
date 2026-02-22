class Solution {
public:
    int countNegatives(vector<vector<int>>& grid) {
        int m = grid.size();          // number of rows
        int n = grid[0].size();       // number of columns
        int count = 0;
        
        int row = m - 1;              // start from bottom-left corner
        int col = 0;
        
        while (row >= 0 && col < n) {
            if (grid[row][col] < 0) {
                // all elements to the right of this are also negative
                count += (n - col);
                row--;                // move up
            } else {
                col++;                // move right
            }
        }
        
        return count;
    }
};
