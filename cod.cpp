#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    vector<int> input;

    cin >> n;

    int x;
    cin >> x;
    input.push_back(x);

    for (int i = 0; i < n - 1; i++) {
        int* temp = new int;
        cin >> *temp;

        if (*temp < input[0]) {
            input.insert(input.begin(), *temp);
        } else if (*temp > input[input.size() - 1]) {
            input.push_back(*temp);
        }

        std::cout << std::endl;
        delete temp;
    }

    std::cout << input[input.size() - 1] << " " << input[0];
}