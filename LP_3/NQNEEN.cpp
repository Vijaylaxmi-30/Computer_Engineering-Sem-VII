
#include <iostream>
#include <vector>
using namespace std;

// Check whether placing queen is safe
bool isSafe(vector<vector<int>>& board,
            int row, int col, int n)
{
    // Check same column
    for (int i = 0; i < row; i++)
    {
        if (board[i][col] == 1)
            return false;
    }

    // Check upper-left diagonal
    int i = row - 1;
    int j = col - 1;

    while (i >= 0 && j >= 0)
    {
        if (board[i][j] == 1)
            return false;

        i--;
        j--;
    }

    // Check upper-right diagonal
    i = row - 1;
    j = col + 1;

    while (i >= 0 && j < n)
    {
        if (board[i][j] == 1)
            return false;

        i--;
        j++;
    }

    return true;
}

// Solve N-Queens using Backtracking
bool solveNQueens(vector<vector<int>>& board,
                  int row, int n)
{
    // All queens placed
    if (row == n)
        return true;

    // Try each column
    for (int col = 0; col < n; col++)
    {
        if (isSafe(board, row, col, n))
        {
            // Place queen
            board[row][col] = 1;

            // Place next queen
            if (solveNQueens(board, row + 1, n))
                return true;

            // Backtrack
            board[row][col] = 0;
        }
    }

    return false;
}

// Display chessboard
void displayBoard(vector<vector<int>>& board, int n)
{
    cout << "\nChessboard:\n";

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

int main()
{
    int choice, n;

    do
    {
        cout << "\n\n--- N-QUEENS MENU ---";
        cout << "\n1. Solve N-Queens";
        cout << "\n2. Exit";

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
            {
                cout << "Enter board size N: ";
                cin >> n;

                if (n < 1 || n > 15)
                {
                    cout << "Enter N between 1 and 15!";
                    break;
                }

                vector<vector<int>> board(
                    n, vector<int>(n, 0)
                );

                // Place first queen at (0,0)
                board[0][0] = 1;

                // Start placing remaining queens
                if (solveNQueens(board, 1, n))
                {
                    cout << "\nSolution Found!";
                    displayBoard(board, n);
                }
                else
                {
                    cout << "\nNo solution exists "
                         << "with first queen at (0,0).";
                }

                break;
            }

            case 2:
                cout << "Exiting program...";
                break;

            default:
                cout << "Invalid choice!";
        }

    } while (choice != 2);

    return 0;
}
