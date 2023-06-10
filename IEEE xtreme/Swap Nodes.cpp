#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

vector<int> inorderTraversal(vector<vector<int>>& tree, int node, vector<int>& result) {

    //base condition
    if (node == -1)
        return result;

    inorderTraversal(tree, tree[node - 1][0], result);
    result.push_back(node);
    inorderTraversal(tree, tree[node - 1][1], result);

    return result;
}

void swapMultiNodes(vector<vector<int>>& tree, int node, int level, int k) {
    
    //base condition 
    if (node == -1)
        return;

    //swaaping left and right subtrees
    if (level % k == 0) {
        int temp = tree[node - 1][0];
        tree[node - 1][0] = tree[node - 1][1];
        tree[node - 1][1] = temp;
    }

    swapMultiNodes(tree, tree[node - 1][0], level + 1, k);
    swapMultiNodes(tree, tree[node - 1][1], level + 1, k);
}

vector<vector<int>> swapNodes(vector<vector<int>> indexes, vector<int> queries) {

    int n = indexes.size();
    vector<vector<int>> result;

    vector<vector<int>> tree(n, vector<int>(2));
    for (int i = 0; i < n; i++) {
        tree[i][0] = indexes[i][0];
        tree[i][1] = indexes[i][1];
    }

    //swapping
    for (int k : queries) {
        
        //swapping nodes at multiples of k
        swapMultiNodes(tree, 1, 1, k);

        //in-order traversal
        vector<int> traversalResult;
        traversalResult = inorderTraversal(tree, 1, traversalResult);
        result.push_back(traversalResult);
    }

    return result;
}

int main()
{
    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    vector<vector<int>> indexes(n);

    for (int i = 0; i < n; i++) {
        indexes[i].resize(2);

        string indexes_row_temp_temp;
        getline(cin, indexes_row_temp_temp);

        vector<string> indexes_row_temp = split(rtrim(indexes_row_temp_temp));

        for (int j = 0; j < 2; j++) {
            int indexes_row_item = stoi(indexes_row_temp[j]);

            indexes[i][j] = indexes_row_item;
        }
    }

    string queries_count_temp;
    getline(cin, queries_count_temp);

    int queries_count = stoi(ltrim(rtrim(queries_count_temp)));

    vector<int> queries(queries_count);

    for (int i = 0; i < queries_count; i++) {
        string queries_item_temp;
        getline(cin, queries_item_temp);

        int queries_item = stoi(ltrim(rtrim(queries_item_temp)));

        queries[i] = queries_item;
    }

    vector<vector<int>> result = swapNodes(indexes, queries);

    for (size_t i = 0; i < result.size(); i++) {
        for (size_t j = 0; j < result[i].size(); j++) {
            cout << result[i][j];

            if (j != result[i].size() - 1) {
                cout << " ";
            }
        }

        if (i != result.size() - 1) {
            cout << "\n";
        }
    }

    cout << "\n";

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
