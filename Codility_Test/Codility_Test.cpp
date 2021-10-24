// Codility_Test.cpp : Defines the entry point for the console application.
//

#include "Windows.h"

#include <iostream>
#include <vector>
#include <sstream>

#include <algorithm>

#include <string>
#include <stack>

typedef __int64 varint;

using namespace std;

//
// LIVE PROBLEM TEST - 1
// FIND A BUG IN THE PROBLEM
// INPUT TWO ARRAYS
// TO FIND THE SMALLEST COMMON UNSIGNED POSITIVE INTEGER
// NOTE -
// IF NOT FOUND RETURN -1
//

int solution1(vector<int> &A, vector<int> &B) {

	int szA = A.size();
	int szB = B.size();

	sort(A.begin(), A.end());
	sort(B.begin(), B.end());

	int i = 0;
	

	//for (int k = 0; k < szA; k++) -- original
	for (int k = 0; k < szA; ) // modified as fix
	{
		if(i < szB -1 && B[i] < A[k])
			i++;

		if (A[k] == B[i])
			return A[k];

		if (k < szA - 1) // added as fix ; ABSENT IN ORGINAL CODE
			k++;		// added as fix ; ABSENT IN ORGINAL CODE
	}

	return -1;
}


//
// LIVE PROBLEM TEST - 2
// WRITE CODE TO GET A ZIPPED (REFORMATTED) NUMBER AS PER BELOW INSTRUCTION
// INPUT A, B INTEGER NUMBERS
// RETURN A[0]B[0]A[1]B[1]A[2]B[2]A[3]B[3]....
// NOTE -
// a=13579 ; B=24680 => OUTPUT C=1234567890
// a=135790011 ; B=246 => OUTPUT C=123456790011

#define NEWLINE std::cout<< endl;

template<typename TV, typename TN>
int extract_digits_in_order(vector<TV>& vint, TN num) 
{
    stringstream ss;
    ss << num;
    if (ss.str().size() == 1)
    {
        vint.push_back(num);
        return vint.size();
    }

    int len = ss.str().size() - 1;
    while (len)
    {
        TN divisor = pow(10, len);
        vint.push_back(num / divisor);
        num = num % divisor;
        --len;
        if (!len)
        {
            vint.push_back(num);
        }
    }

    return vint.size();
}

void main()
{
    vector<int> vInt1, vInt2;;
    unsigned  num1 = 13579;
    unsigned  num2 = 2;

    int d1 = extract_digits_in_order(vInt1, num1);
    int d2 = extract_digits_in_order(vInt2, num2);
    unsigned maxlen = d1 > d2 ? d1 : d2;
    NEWLINE
    for (unsigned i = 0; i < maxlen; ++i)
    {
        if (i < vInt1.size())
            cout << vInt1[i] << " ";
        else
        {
            for_each(vInt2.begin() + i, vInt2.end(), [](const auto& elem) {
                cout << elem << " ";
                });
            break;
        }
        if (i < vInt2.size())
            cout << vInt2[i] << " ";
        else
        {
            for_each(vInt1.begin() + i, vInt1.end(), [](const auto& elem) {
                cout << elem << " ";
                });
            break;
        }
    }

    return 0;
}


//
// LIVE PROBLEM TEST - 3
// WRITE A MACHINE THAT PROCESS A STRING INPUT AND GET INTEGER OUTPUT
// INPUT STRING - "13+62*7+*"
// RETURN FORMAT ANSWER - (1+3)*((6*2)+7) = 76
// NOTE - SHOULD REPORT OVER/UNDERFLOW/INVALID 
// 
// INTEGERS TO PUSH ON STACK 
// OPERATORS TO POP THE STACK AND DO OPERATION AND PUSH AGAIN ON STACK

int solution3(string S)
{

	std::stack <int> v;
	for (int i = 0; i< S.length(); ++i)
	{
		char a = S.at(i);
		int val = -1;
		if (a == '0' || a == '1' ||
			a == '2' || a == '3' ||
			a == '4' || a == '5' ||
			a == '6' || a == '7' ||
			a == '8' || a == '9')
		{
			char t[4] = "\0";
			sprintf(t, "%c", a);
			val = atoi(t);
			v.push(val);
			//cout << val;
		}

		if (a == '+' || a == '*')
		{
			if (v.empty())
				return -1;

			int v1 = v.top();
			v.pop();

			if (a == '+')
			{
				if (v.empty())
					return -1;

				int v2 = v.top();
				v.pop();
				int sum = v1 + v2;

				v.push(sum);
			}
			if (a == '*')
			{
				if (v.empty())
					return -1;

				int v2 = v.top();
				v.pop();
				int product = v1*v2;

				v.push(product);
			}

		}

	}
	
	if (v.empty())
		return -1;
	
	int finalval = v.top();
	v.pop();

	if (v.empty())
		return finalval;

	else
		return -1;

}

//
// SAMPLE PRACTICE PROBLEM TEST - 1
// FIND A EQUILIBRIUM POINT IN AN ARRAY
// EQUILIBRIUM POINT IS DEFINED AS THE LEFT ELEMENT SUM SHOULD BE EQUAL TO 
// SUM OF THE RIGHT ELEMENTS
// NOTE -
// FOR ENDPOINTS EQUILIBRIUM SUM IS 0
//

typedef struct node {
	INT64 index;
	INT64 data;
	INT64 sum_prefix;
	INT64 sum_suffix;
	node *next;
	node *pre;
}NODE, *PNODE;

INT64 A(INT64 arr[], INT64 len) //INT64 input[] = {-1,3,-4,5,1,-6,2,1};
{

	INT64 count = 0;
	NODE* head = (NODE*)malloc(sizeof(NODE));
	head->data = arr[count];
	head->sum_prefix = 0;
	head->sum_suffix = 0;
	head->next = head->pre = NULL;
	head->index = count;

	NODE* tail = head;
	INT64 sum = head->data;
	NODE* tmp = NULL;

	while (++count < len)
	{
		tmp = (NODE*)malloc(sizeof(NODE));
		tmp->data = arr[count];
		tmp->sum_prefix = 0;
		tmp->sum_suffix = 0;
		tmp->index = count;

		tmp->next = NULL;
		tmp->pre = tail;
		tmp->sum_prefix = sum;
		sum += tmp->data;

		tail->next = tmp;
		tmp->pre = tail;
		tail = tmp;
	}

	tmp = tail->pre;
	//trav backwards
	sum = tail->data;
	while (tmp != NULL)
	{
		tmp->sum_suffix = sum;
		sum += tmp->data;
		tmp = tmp->pre;
	}

	//INT64 counter = 0;
	tmp = head;
	while (tmp != NULL)
	{
		//printf("\n[%lld, %lld, %lld, %lld] ", tmp->index, tmp->data, tmp->sum_prefix, tmp->sum_suffix);
		if (tmp->sum_prefix == tmp->sum_suffix)
		{
			//printf(" === This is answer = %lld\n", tmp->index);
			return tmp->index;
		}

		tmp = tmp->next;

		//counter++;

	}

	if (tmp == NULL)
		return -1;
}
//
// SAMPLE PRACTICE PROBLEM TEST - 1 
//- ARRAY BASED ALTERNATE SOLUTION
//
INT64 A2(INT64 arr[], INT64 len)
{
	INT64 sum_suffix = 0;
	INT64 sum_prefix = 0;

	INT64 counter = 0;

	for (UINT64 i = 0; i < len; ++i)
	{
		sum_suffix = 0;
		sum_prefix = 0;

		for (UINT64 j = i + 1; j < len && j < len; ++j)
		{
			sum_suffix += arr[j];
		}
		for (UINT64 k = 0; k < i && i > 0; ++k)
		{
			sum_prefix += arr[k];
		}

		printf("\n[%lld, %lld, %lld, %lld] ", i, arr[i], sum_prefix, sum_suffix);

		if (sum_suffix == sum_prefix)
		{
			//printf(" === This is answer = %lld\n", i );
			return i;
		}

		counter = i;
	}
	if (counter == len - 1)
		return -1;

}


//
//
// SAMPLE PRACTICE PROBLEM TEST - 2
// FIND A SMALLEST MISSING INTEGER IN ARRAY
// INPUT ARRAY - 23456 - ANSWER = 1
// INPUT ARRAY - 123456 - ANSWER = 7
// INPUT ARRAY - -1,-3,-4 - ANSWER = 1
// INPUT ARRAY - 7,8,9,10 - ANSWER = 1
//

typedef vector<INT64> vINT64;

INT64 solution5(vINT64 &vInput)
{

	sort(vInput.begin(), vInput.end());
	//vInput.erase(unique(vInput.begin(), vInput.end()), vInput.end());

	INT64 hi = vInput[vInput.size() - 1];
	if (hi <= 0)
		return 1;

	vINT64::iterator it = vInput.begin();

	INT64 now = 1;

	while (it != vInput.end())
	{
		if (*it < 0)
			it++;
		else
		{
			if (*it < now)
				it++;
			else if (*it == now)
			{
				it++;
				now++;
			}
			else
				return now;
		}

	}

	return hi + 1;
}
100% result


//Write a function :
//int solution(int A[], int N);
//that, given an array A of N integers, returns the smallest positive integer(greater than 0) that does not occur in A.
//For example, given A = [1, 3, 6, 4, 1, 2], the function should return 5.
//Given A = [1, 2, 3], the function should return 4.
//Given A = [−1, −3], the function should return 1.
//Write an efficient algorithm for the following assumptions :
//N is an integer within the range[1..100, 000];
//each element of array A is an integer within the range[−1, 000, 000..1, 000, 000].
#include <algorithm>
using namespace std;
int solution(vector<int>& A) {
    // write your code in C++14 (g++ 6.2.0)
    //1 - make local copy
    vector<int> vInt2 = A;
    //2 - sort input
    sort(vInt2.begin(), vInt2.end());
    //3 - get only positive values negative and 0 excluded
    vector <int> trunc;
    trunc.push_back(0);
    for_each(vInt2.begin(), vInt2.end(), [&trunc](const auto& elem) {
        if (elem > 0)
        {
            trunc.push_back(elem);
        }
        
    });
    
    //5- decision if all zero values hence trunc is empty return 1
    if (trunc.empty())
        return 1;

    //6-start comparing from 0 to highest number in truncated vector
    for (int i = 0; i < trunc[trunc.size()-1]; ++i)
    {
        if (i != trunc[i])
            return i;
    }

    //7-if all numbers are present, then the next number to the highest is answer
    return  trunc[trunc.size() - 1] + 1;
}


//24-OCT-2021
//Find strokes to color the vertical buildings, height of building is index data
//Brush stroke is increased if no building connected of same height
int solution(vector<int>& A) 
{
    auto vec = A;
    double max = 0;
    //find highest building
    for (unsigned i = 0; i < vec.size(); ++i)
    {
        if (vec[i] > max)
            max = vec[i];
    }
    int bc = 0;
    for (unsigned iteration = 1; iteration <= max +1 ; ++iteration)
    {
        bool stroked = false;
        NEWLINE
        int nonzeroelem = 0;
        for_each(vec.begin(), vec.end(), [&nonzeroelem](const auto& elem) {
            if (nonzeroelem > 1) return;
            if (elem > 0)
                ++nonzeroelem;
            });
        if (nonzeroelem <= 1)
        {
	    //if 1000000000 is alone building height, cut it short
            auto newlen = bc + (max - iteration+1);
            return newlen;
        }
        for (unsigned i = 0; i < vec.size() ; ++i)
        {
            if (i == vec.size() - 1 )
            {
                if (!stroked && vec[i])
                    ++bc;
                if(vec[i] > 0 )
                    --vec[i];
                continue;
            }
            if (vec[i] == 0 && vec[i + 1] > 0){//0 - 1
                stroked = false;
                continue;
            }
            if (vec[i] > 0 && vec[i + 1] == 0) {//1 - 0
                --vec[i];
                if (!stroked)
                    ++bc;
                stroked = true;
                continue;
            }
            if (vec[i] > 0 && vec[i + 1] > 0){//1 - 1
                if(!stroked)
                    ++bc;
                stroked = true;
                --vec[i];
                continue;
            }
            if (vec[i] == 0 && vec[i + 1] == 0){ //0 - 0
                stroked = false;
                continue;
            }
        }
        std::cout << " bc=" <<  bc << endl;
    }
    return bc;
}


int main()
{
	
	//sort(vec.begin(), vec.end());
	//vec.erase(unique(vec.begin(), vec.end()), vec.end());
	
	//vector<int > A = {1,2,3,4,9};
	//vector<int > B = { 5,6,7,8,9 };

	//cout << "Solution 1.1 -> " << solution1(A, B) << endl;

	//vector<int > A1 = { 2,3,4,5,6,1 };
	//vector<int > B1 = { 9,10,7,8,2 };

	//cout << "Solution 1.2 -> " << solution1(A1, B1) << endl;

	//vector<int > A2 = { 4,4,2,3,1,6,5 };
	//vector<int > B2 = { 4,5,5,1,1 };

	//cout << "Solution 1.3 -> " << solution1(A2, B2) << endl;


//	cout << "Solution 2.1 -> " << solution2(1234567890LL, 1234567890LL) << endl;
//	cout << "Solution 2.1 -> " << solution2(102030405060708090LL, 102030405060708090LL) << endl;

	string s = "13+62*7+*";
	cout << solution3(s);


	//solution 4 input space
	//INT64 input[] = { -2147483648LL, 0, -2147483648LL };// {-1, 3, -4, 5, 1, -6, 2, 1};
	INT64 input[] = { -1, 3, -4, 5, 1, -6, 2, 1 };

	INT64 val = A(input, sizeof(input) / sizeof(input[0]));
	printf("\nOutput A is = %lld\n", val);

	INT64 val2 = A2(input, sizeof(input) / sizeof(input[0]));
	printf("\nOutput A2 is = %lld\n", val2);


	//solution 5 input space

	//vINT64 input = {1, 3, 6, 4, 1, 2};
	//vINT64 input = { 4, 5, 3, 2, 1 };
	vINT64 vInput = { 0 };

	for (INT64 i = -10; i <= 100; ++i)
		vInput.push_back(i);
	//vINT64 input = { -1000000,1000000 };

	int out = solution5(vInput);

	cout << out << endl;
    return 0;
}

