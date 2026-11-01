
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int dp[101][1001];

int weight[101], value[101];
int n, capacity;
bool solved = false;

// Function to solve 0/1 Knapsack
int knapsack()
{
    // Initialize DP table
    for (int i = 0; i <= n; i++)
    {
        for (int w = 0; w <= capacity; w++)
        {
            if (i == 0 || w == 0)
            {
                dp[i][w] = 0;
            }
            else if (weight[i - 1] <= w)
            {
                dp[i][w] = max(
                    value[i - 1] + dp[i - 1][w - weight[i - 1]],
                    dp[i - 1][w]
                );
            }
            else
            {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    return dp[n][capacity];
}

// Display DP table
void displayTable()
{
    cout << "\nDP Table:\n";

    for (int i = 0; i <= n; i++)
    {
        for (int w = 0; w <= capacity; w++)
        {
            cout << dp[i][w] << "\t";
        }
        cout << endl;
    }
}

// Display selected items
void displaySelectedItems()
{
    int w = capacity;

    cout << "\nSelected Items:\n";

    for (int i = n; i > 0; i--)
    {
        if (dp[i][w] != dp[i - 1][w])
        {
            cout << "Item " << i
                 << " (Weight = " << weight[i - 1]
                 << ", Value = " << value[i - 1] << ")\n";

            w = w - weight[i - 1];
        }
    }
}

int main()
{
    int choice;

    do
    {
        cout << "\n\n--- 0/1 KNAPSACK MENU ---";
        cout << "\n1. Enter Items and Solve";
        cout << "\n2. Display DP Table";
        cout << "\n3. Exit";

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                cout << "Enter number of items: ";
                cin >> n;

                if (n <= 0 || n > 100)
                {
                    cout << "Invalid number of items!";
                    solved = false;
                    break;
                }

                cout << "Enter weights of items:\n";

                for (int i = 0; i < n; i++)
                {
                    cin >> weight[i];

                    if (weight[i] <= 0)
                    {
                        cout << "Weight must be positive!";
                        n = 0;
                        break;
                    }
                }

                if (n == 0)
                {
                    solved = false;
                    break;
                }

                cout << "Enter values of items:\n";

                for (int i = 0; i < n; i++)
                {
                    cin >> value[i];
                }

                cout << "Enter knapsack capacity: ";
                cin >> capacity;

                if (capacity < 0 || capacity > 1000)
                {
                    cout << "Invalid capacity!";
                    solved = false;
                    break;
                }

                cout << "\nMaximum Profit = "
                     << knapsack() << endl;

                displaySelectedItems();

                solved = true;
                break;

            case 2:
                if (!solved)
                {
                    cout << "Please solve the problem first!";
                }
                else
                {
                    displayTable();
                }
                break;

            case 3:
                cout << "Exiting program...";
                break;

            default:
                cout << "Invalid choice!";
        }

    } while (choice != 3);

    return 0;
}
