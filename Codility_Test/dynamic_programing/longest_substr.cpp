
#include <string>
using namespace std;



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