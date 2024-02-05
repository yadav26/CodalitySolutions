
#include <iostream>
#include <string>
#include <map>
using namespace std;


//Get all substrings 
//important ratta maro
map<string, int> mu;

//Here it will return all substrings
void getallsubstr(const string& s, int start, int end) {
    if (start >= s.size())return;
    if (end >= s.size() + 1) {
        getallsubstr(s, start + 1, start + 2);
        return;
    }
    cout << endl << s.substr(start, end - start);
    mu[s.substr(start, end - start)] += 1;
    getallsubstr(s, start, end + 1);
}

//here we get all possible subsequences
int getallsubseq(int i, string& s, string& sc) {
    if (i == s.size())
    {
        cout << sc << endl;
        return 0;
    }
    sc.push_back(s[i]);
    getallsubseq(i + 1, s, sc);
    sc.pop_back();
    getallsubseq(i + 1, s, sc);
}

//here we get all possible subsequences integer values
int getallsubseqInt(int i, vector<int>& s, vector<int>& sc) {
    if (i == s.size())
    {
        cout << endl;
        for(auto&el: sc)cout << el << ",";
        return 0;
    }
    sc.push_back(s[i]);
    getallsubseqInt(i + 1, s, sc);
    sc.pop_back();
    getallsubseqInt(i + 1, s, sc);
}
//below still to be checked if correct
int longest_substr(int i, int j , std::string& s1, std::string &s2){
    if(i<0 || j<0) return 0;
    int ans = 0;
    if(s1[i]==s2[j])
        ans = max(ans, longest_substr(i-1,j-1,s1,s2)+1);

    ans = max(ans, longest_substr(i-1,j,s1,s2));
    ans = max(ans, longest_substr(i,j-1,s1,s2));
}

int main(){

    string s1 = "abcde";
    string s2 = "bcacde";
    return longest_substr(s1.size()-1, s2.size()-1, s1, s2);
}