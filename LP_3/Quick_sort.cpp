
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
using namespace std;
using namespace chrono;

// Random number generator
mt19937 rng(random_device{}());

// Count comparisons
long long comparisons = 0;

// Deterministic Partition
int partitionArray(vector<int>& a, int low, int high)
{
    int pivot = a[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        comparisons++;

        if (a[j] <= pivot)
        {
            i++;
            swap(a[i], a[j]);
        }
    }

    swap(a[i + 1], a[high]);

    return i + 1;
}

// Deterministic Quick Sort
void quickSort(vector<int>& a, int low, int high)
{
    if (low < high)
    {
        int p = partitionArray(a, low, high);

        quickSort(a, low, p - 1);
        quickSort(a, p + 1, high);
    }
}

// Randomized Partition
int randomPartition(vector<int>& a, int low, int high)
{
    uniform_int_distribution<int> dist(low, high);

    int randomIndex = dist(rng);

    swap(a[randomIndex], a[high]);

    return partitionArray(a, low, high);
}

// Randomized Quick Sort
void randomizedQuickSort(vector<int>& a,
                         int low, int high)
{
    if (low < high)
    {
        int p = randomPartition(a, low, high);

        randomizedQuickSort(a, low, p - 1);
        randomizedQuickSort(a, p + 1, high);
    }
}

// Display Array
void displayArray(const vector<int>& a)
{
    for (int x : a)
        cout << x << " ";

    cout << endl;
}

int main()
{
    vector<int> arr;
    int choice, n;

    do
    {
        cout << "\n\n--- QUICK SORT MENU ---";
        cout << "\n1. Enter Array";
        cout << "\n2. Deterministic Quick Sort";
        cout << "\n3. Randomized Quick Sort";
        cout << "\n4. Compare Both Algorithms";
        cout << "\n5. Exit";

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                cout << "Enter number of elements: ";
                cin >> n;

                if (n <= 0)
                {
                    cout << "Invalid array size!";
                    arr.clear();
                    break;
                }

                arr.resize(n);

                cout << "Enter array elements:\n";

                for (int i = 0; i < n; i++)
                    cin >> arr[i];

                cout << "Array stored successfully!";
                break;

            case 2:
            {
                if (arr.empty())
                {
                    cout << "Enter array first!";
                    break;
                }

                vector<int> a = arr;
                comparisons = 0;

                auto start = high_resolution_clock::now();

                quickSort(a, 0, a.size() - 1);

                auto stop = high_resolution_clock::now();

                auto duration =
                    duration_cast<microseconds>(stop - start);

                cout << "\nSorted Array: ";
                displayArray(a);

                cout << "Comparisons: " << comparisons;
                cout << "\nExecution Time: "
                     << duration.count() << " microseconds";

                break;
            }

            case 3:
            {
                if (arr.empty())
                {
                    cout << "Enter array first!";
                    break;
                }

                vector<int> a = arr;
                comparisons = 0;

                auto start = high_resolution_clock::now();

                randomizedQuickSort(a, 0, a.size() - 1);

                auto stop = high_resolution_clock::now();

                auto duration =
                    duration_cast<microseconds>(stop - start);

                cout << "\nSorted Array: ";
                displayArray(a);

                cout << "Comparisons: " << comparisons;
                cout << "\nExecution Time: "
                     << duration.count() << " microseconds";

                break;
            }

            case 4:
            {
                if (arr.empty())
                {
                    cout << "Enter array first!";
                    break;
                }

                vector<int> a = arr;
                vector<int> b = arr;

                comparisons = 0;

                auto start1 = high_resolution_clock::now();

                quickSort(a, 0, a.size() - 1);

                auto stop1 = high_resolution_clock::now();

                long long detComparisons = comparisons;

                auto detTime =
                    duration_cast<microseconds>(stop1 - start1);

                comparisons = 0;

                auto start2 = high_resolution_clock::now();

                randomizedQuickSort(b, 0, b.size() - 1);

                auto stop2 = high_resolution_clock::now();

                long long randComparisons = comparisons;

                auto randTime =
                    duration_cast<microseconds>(stop2 - start2);

                cout << "\nDeterministic Quick Sort:";
                cout << "\nComparisons: " << detComparisons;
                cout << "\nTime: " << detTime.count()
                     << " microseconds";

                cout << "\n\nRandomized Quick Sort:";
                cout << "\nComparisons: " << randComparisons;
                cout << "\nTime: " << randTime.count()
                     << " microseconds";

                cout << "\n\nBoth arrays sorted successfully.";

                break;
            }

            case 5:
                cout << "Exiting program...";
                break;

            default:
                cout << "Invalid choice!";
        }

    } while (choice != 5);

    return 0;
}
