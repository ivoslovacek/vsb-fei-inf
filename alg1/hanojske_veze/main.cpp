#include <iostream>
#include <stack>

using namespace std;

class towers
{
public:
    towers(int disk_count = 4)
    {
        if (disk_count > 0)
        {
            this->disk_count = disk_count;
        }
        else
        {
            this->disk_count = 4;
        }

        for (int i = disk_count; i > 0; i--)
        {
            this->A.push(i);
        }
    }

    void getTowers()
    {
        stack<int> A = this->A;
        stack<int> B = this->B;
        stack<int> C = this->C;

        for (size_t i = this->disk_count; i > 0; i--)
        {
            if (A.size() < i)
            {
                cout << "| ";
            }
            else
            {
                cout << A.top() << " ";
                A.pop();
            }

            if (B.size() < i)
            {
                cout << "| ";
            }
            else
            {
                cout << B.top() << " ";
                B.pop();
            }

            if (C.size() < i)
            {
                cout << "| ";
            }
            else
            {
                cout << C.top() << " ";
                C.pop();
            }

            cout << endl;
        }
        cout << "A B C" << endl;
    }

    void solve()
    {
        solve(this->disk_count, this->A, this->C, this->B);
    }

    void solve(int N, stack<int>& from, stack<int>& to, stack<int>& aux)
    {
        if (N > 0)
        {
            solve(N - 1, from, aux, to);
            moveDisk(from, to);
            this->getTowers();
            solve(N - 1, aux, to, from);
        }
    }

    void moveDisk(stack<int> &from, stack<int> &to)
    {
        to.push(from.top());
        from.pop();
    }

private:
    int disk_count;
    stack<int> A;
    stack<int> B;
    stack<int> C;
};

int main()
{
    towers veze(9);

    veze.getTowers();

    veze.solve();

    veze.getTowers();

    return 0;
}