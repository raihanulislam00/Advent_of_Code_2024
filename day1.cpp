#include <iostream>
#include <queue>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    // We create two queues to represent the left and right lists
    priority_queue<int> left_q;
    priority_queue<int> right_q;

    // The string structure to represent the current line
    string current_line;

    int first_num, second_num;

    // A big part of the Advent of Code is parsing and
    // storing the challenge's input.
    while (getline(cin, current_line))
    {
        int first_space = current_line.find_first_of(' ');
        int last_space = current_line.find_last_of(' ');

        // Get the numbers from the line as substrings and
        // convert them to integers.
        first_num = atoi(current_line.substr(0, first_space).c_str());
        second_num = atoi(current_line.substr(last_space, current_line.size()).c_str());

        left_q.push(first_num);
        right_q.push(second_num);
    }

    // initialize the summation distance
    int sum_distances = 0;

    // Go until we have exhausted the input.
    while (!left_q.empty())
    {
        int num = left_q.top();
        int num2 = right_q.top();

        // Take the absolute value of the distance
        sum_distances += abs(num - num2);

        // Remove numbers from the tops of the heaps
        left_q.pop();
        right_q.pop();
    }

    cout << sum_distances << endl;

    return 0;
}
