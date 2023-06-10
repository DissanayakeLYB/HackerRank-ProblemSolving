#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

double getMedian(vector<int>& arr, int start, int end) {
    
    int n = end - start + 1;
    int mid = start + n / 2;

    if (n % 2 == 0) {
        return (arr[mid - 1] + arr[mid]) / 2.0;
    }
    
    else {
        return arr[mid];
    }
}

int activityNotifications(vector<int>& expenditure, int d) {
    
    int n = expenditure.size();
    int notifications = 0;
    vector<int> trailExpend(d);

    for (int i = 0; i < d; i++) {
        trailExpend[i] = expenditure[i];
    }

    sort(trailExpend.begin(), trailExpend.end());

    for (int i = d; i < n; i++) {
        double median = getMedian(trailExpend, 0, d - 1);
        if (expenditure[i] >= 2 * median) {
            notifications++;
        }

        //updating trailing expenditures
        int remIdx = i - d;
        int insIdx = lower_bound(trailExpend.begin(), trailExpend.end(), expenditure[remIdx]) - trailExpend.begin();
        trailExpend.erase(trailExpend.begin() + insIdx);
        trailExpend.insert(lower_bound(trailExpend.begin(), trailExpend.end(), expenditure[i]), expenditure[i]);
    }

    return notifications;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    int d = stoi(first_multiple_input[1]);

    string expenditure_temp_temp;
    getline(cin, expenditure_temp_temp);

    vector<string> expenditure_temp = split(rtrim(expenditure_temp_temp));

    vector<int> expenditure(n);

    for (int i = 0; i < n; i++) {
        int expenditure_item = stoi(expenditure_temp[i]);

        expenditure[i] = expenditure_item;
    }

    int result = activityNotifications(expenditure, d);

    fout << result << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
