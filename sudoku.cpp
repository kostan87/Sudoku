#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Cells {
	public:
		void set_value(int value_) {
      value = value_;
    }

    int get_value() {
      return value;
    }
		
		void set_values(const std::vector <int> &arr) {
			for (int i = 0; i < 9; i++) {
				values[i] = arr[i];
			}
		}

		std::vector <int> get_values() {
			return values;
		}
	private:
		int value = 0;
		vector <int> values = vector <int> (9);	
};

vector <int> filter(vector <int> &src, const vector <int> &filter) {
  for (int i = 0; i < 9; i++) {
    for (int n = 0; n < 9; n++) {
      if (filter[n] != 0) {
        if (src[i] == filter[n])
          src[i] = 0;
      }
    }
  }
  return src;
}

vector <vector <Cells>> set_values(vector <vector <Cells>> &arr, vector <int> &values) {
	for (int i = 0, k = 0; i < 9; i++) {
		for (int n = 0; n < 9; n++) {
			if (values[k] != 0)
				arr[i][n].set_value(values[k]);
			k++;
		}
	}
	return arr;
}

void print_values(vector <vector <Cells>> &arr) {
	for (int i = 0; i < 9; i++) {
		for (int n = 0; n < 9; n++) {
			cout << arr[i][n].get_value() << " ";
			if ((n + 1) % 9 == 0) {
				cout << endl;
			}
		}
	}
}

int get_progress(vector <vector <Cells>> &arr) {
	int values_cout = 0;
	for (int i = 0; i < 9; i++) {
		for (int n = 0; n < 9; n++) {
			if (arr[i][n].get_value() != 0) {
				++values_cout;
			}
		}
	}
	return values_cout;
}

vector <vector <Cells>> processing_values(vector <vector <Cells>> &arr) {
  int values_cout, value, m;
  vector <int> values(9), row_values(9), column_values(9), square_values(9);
  vector <int> sqn = {1, 2, 3, 4, 5, 6, 7, 8, 9};

	for (int i = 0; i < 9; i++) {
		for (int n = 0; n < 9; n++) {
			if (arr[i][n].get_value() == 0) {
				value = 0;
				values_cout = 0;
				for (int a = 0; a < 9; a++) {
					if (arr[i][n].get_values()[a] != 0) {
						value = arr[i][n].get_values()[a];
						values_cout += 1;
					}
				}
				if (values_cout == 1) {
					arr[i][n].set_value(value);
				} else {
					m = 0;
					for (int k = 0; k < 9; k++) {
						row_values[k] = arr[i][k].get_value();
						column_values[k] = arr[k][n].get_value();
						for (int l = 0; l < 9; l++) {
							if ((k / 3) == (n / 3) and (l / 3) == (i / 3)) {
								square_values[m] = arr[l][k].get_value();
								++m;
							}
						}
					}
					sqn = {1, 2, 3, 4, 5, 6, 7, 8, 9};
					values = filter(sqn, row_values);
					values = filter(values, column_values);
					values = filter(values, square_values);
					arr[i][n].set_values(values);
				}
			}
		}
	}
	return arr;
}

int main() {
	vector <vector <Cells>> arr(9, vector <Cells> (9));
	vector <int> values = {
    0, 1, 2, 0, 0, 0, 5, 9, 0,
    3, 8, 0, 0, 1, 0, 0, 6, 7,
    6, 0, 5, 4, 8, 9, 3, 0, 1,
    0, 0, 6, 0, 2, 0, 7, 0, 0,
    0, 4, 7, 6, 0, 3, 8, 1, 0,
    0, 0, 1, 0, 5, 0, 6, 0, 0,
    1, 0, 8, 7, 3, 2, 9, 0, 4,
    7, 5, 0, 0, 4, 0, 0, 8, 6,
    0, 2, 4, 0, 0, 0, 1, 7, 0
  };
	arr = set_values(arr, values);
	print_values(arr);
	cout << endl;
	while (get_progress(arr) != 81) {
		arr = processing_values(arr);
	}
	print_values(arr);
	return 0;
}