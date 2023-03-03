#include <iostream>
#include <string>
#include <chrono>

using namespace std;

int *input_arr()
/*Inputs and stores 81 sequential values at a location. For details on input format, see input prompt*/
{
    int cg[9][9];

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            cg[i][j] = 0;
        }
    }

    string input_line;
    cout << "Please enter all 81 elements in a single string of numbers, read row-wise, 0 for empty place, no spaces\n>>> ";

    cin >> input_line;

    int indie = 0;

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            cg[i][j] = input_line[indie] - '0';
            indie++;
        }
    }

    int *ret = cg[0];

    cout << "\n\n";

    return ret;
}

bool find_empty(int cg[9][9], int *coord_ptr)
/*coor_ptr is a pointer to an array of 2 elements that stores coordinates of next empty space*/
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (cg[i][j] == 0)
            {
                *coord_ptr = i;
                coord_ptr++;
                *coord_ptr = j;
                return true;
            }
        }
    }
    *coord_ptr = -1;
    coord_ptr++;
    *coord_ptr = -1;
    return false;
}

bool safe_in_row(int cg[9][9], int rowi, int val)
/*rowi is row number and val is possible value*/
{

    for (int i = 0; i < 9; i++)
    {
        if (cg[rowi][i] == val)
        {
            return false;
        }
    }

    return true; // If it passes all conditions
}

bool safe_in_col(int cg[9][9], int coli, int val)
/*coli is column number and val is possible value*/
{

    for (int i = 0; i < 9; i++)
    {
        if (cg[i][coli] == val)
        {
            return false;
        }
    }

    return true; // If it passes all conditions
}

bool safe_in_box(int cg[9][9], int i1, int j1, int val)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (cg[i1 + i][j1 + j] == val)
            {
                return false;
            }
        }
    }

    return true;
}

bool is_safe_here(int cg[9][9], int i12, int j12, int val)
{
    return (safe_in_row(cg, i12, val) && safe_in_col(cg, j12, val) && safe_in_box(cg, (3 * int(i12 / 3)), (3 * int(j12 / 3)), val));
}

int backtracks = 0;

bool bruteforce(int cg[9][9])
{
    int loc[2];

    int *cod_ptr = loc;

    if (!find_empty(cg, cod_ptr))
    {
        return true;
    }

    int il = loc[0];
    int jl = loc[1];

    for (int pv = 1; pv <= 9; pv++)
    {
        if (is_safe_here(cg, il, jl, pv))
        {
            cg[il][jl] = pv;

            if (bruteforce(cg))
            {
                return true;
            }

            cg[il][jl] = 0;
        }
    }

    backtracks += 1;

    // if (backtracks % 1000 == 0)
    // {
    //     cout << "Backtracks:" << backtracks << '\n';
    // }

    return false;
}

void grid_display(int cg[9][9])
{
    cout << "\n\n";

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            cout << cg[i][j] << " ";
        }

        cout << '\n';
    }
}

int main()
{
    int cg[9][9];

    int *ptr = input_arr();

    int *ptract = ptr;

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            cg[i][j] = *ptract++;
        }
    }

    auto start = chrono::high_resolution_clock::now();

    auto stop0 = chrono::high_resolution_clock::now();

    if (bruteforce(cg))
    {
        stop0 = chrono::high_resolution_clock::now();

        grid_display(cg);
    }

    auto stop = chrono::high_resolution_clock::now();

    cout << "\n\n";

    cout << ((double)chrono::duration_cast<chrono::nanoseconds>(stop0 - start).count()) / 1000000000;

    cout << "\n\n";

    auto nanos = chrono::duration_cast<chrono::nanoseconds>(stop - start).count();

    cout
        << "\n\n"
        << double(nanos) / 1000000000 << "\n";

    cout << backtracks;

    cin.get();

    return 0;
}