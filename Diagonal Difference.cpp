#include bitsstdc++.h

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vectorstring split(const string &);


  Complete the 'diagonalDifference' function below.
 
  The function is expected to return an INTEGER.
  The function accepts 2D_INTEGER_ARRAY arr as parameter.
 

int diagonalDifference(vectorvectorint arr) {
    
    int sumMain = 0;    sum of the main diagonal elements
    int sumSub = 0;    sum of the secondary diagonal elements
    
    int sizeArr = arr.size();
    
    for(int i = 0; i  sizeArr; i++){
        sumMain += arr[i][i];
        sumSub += arr[i][sizeArr-i-1];
    }
    
    int diff = fabs(sumMain - sumSub);   difference of the diagonal elements   
    
    return diff;
}

int main()
{
    ofstream fout(getenv(OUTPUT_PATH));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    vectorvectorint arr(n);

    for (int i = 0; i  n; i++) {
        arr[i].resize(n);

        string arr_row_temp_temp;
        getline(cin, arr_row_temp_temp);

        vectorstring arr_row_temp = split(rtrim(arr_row_temp_temp));

        for (int j = 0; j  n; j++) {
            int arr_row_item = stoi(arr_row_temp[j]);

            arr[i][j] = arr_row_item;
        }
    }

    int result = diagonalDifference(arr);

    fout  result  n;

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_funint, int(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_funint, int(isspace))).base(),
        s.end()
    );

    return s;
}

vectorstring split(const string &str) {
    vectorstring tokens;

    stringsize_type start = 0;
    stringsize_type end = 0;

    while ((end = str.find( , start)) != stringnpos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
