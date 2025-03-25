#include <fstream>
#include <vector>
using namespace std;

bool Branje_Stevil(vector<int> &vec, const char s[]) {
	ifstream input(s);
	int st;

	if (!input.is_open()) {
		return false;
	}

	while (!input.eof()) {
		input >> st;
		vec.push_back(st);
		while (isspace(input.peek())) input.get();
	}
	input.close();
	return true;
}
void Izpis_Stevil(const vector<int>& vec) {
    ofstream output("out.txt");

    for (size_t i = 0; i < vec.size(); i++) {
        output << vec[i] << ' ';
    }
    output.close();
}

// Counting Sort Algorithm
void CountingSort(vector<int>& vec) {
    if (vec.empty()) return;

    int maxVal = *max_element(vec.begin(), vec.end());
    int minVal = *min_element(vec.begin(), vec.end());

    int range = maxVal - minVal + 1;
    vector<int> count(range, 0);
    vector<int> output(vec.size());

    // Count the frequency of each element
    for (int num : vec) {
        count[num - minVal]++;
    }

    // Compute the cumulative sum
    for (int i = 1; i < range; i++) {
        count[i] += count[i - 1];
    }

    // Place the elements in sorted order
    for (int i = vec.size() - 1; i >= 0; i--) {
        output[count[vec[i] - minVal] - 1] = vec[i];
        count[vec[i] - minVal]--;
    }

    // Copy the sorted array back into the original vector
    vec = output;
}


// Roman Sort Algorithm
void RomanSort(vector<int>& vec) {
    if (vec.empty()) return;

    int maxVal = *max_element(vec.begin(), vec.end());
    int minVal = *min_element(vec.begin(), vec.end());

    // Step 1: Create a counting array C
    int range = maxVal - minVal + 1;
    vector<int> count(range, 0);

    // Step 2: Count the occurrences of each number in the vector
    for (int num : vec) {
        count[num - minVal]++;  // Shift numbers to be non-negative
    }

    // Step 3: Create the output vector B
    vector<int> output(vec.size());
    int index = 0;

    // Step 4: Fill the output vector B based on the counts in C
    for (int i = 0; i < range; i++) {
        for (int j = 0; j < count[i]; j++) {
            output[index++] = i + minVal;  // Shift back to the original values
        }
    }

    // Step 5: Copy the sorted array back into the original vector
    vec = output;
}

int main(int argc, const char* argv[]) {
    vector<int> A;

    if (argc < 3) {
        cout << "Insufficient arguments!" << endl;
        return 0;
    }

    if (!Branje_Stevil(A, argv[2])) {
        cout << "Error reading the file!" << endl;
        return 0;
    }

    if (argv[1][0] == '0') {
        // Counting sort
        CountingSort(A);
    }
    else {
        // Roman sort
        RomanSort(A);
    }

    // Output the sorted numbers to out.txt
    Izpis_Stevil(A);

    return 0;
}
