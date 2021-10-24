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

template<typename TV, typename TN>
void extract_digits_in_order(vector<TV>& vint, TN num) 
{
    stringstream ss;
    ss << num;
    int len = ss.str().length() - 1;
    while (len)
    {
        TN divisor = pow(10, len);
        vint.push_back(num / divisor);
        num = num % divisor;
        --len;
        if (!len)
            vint.push_back(num);
    }
}

void main()
{
    vector<int> vInt, vInt2;;
    unsigned  num2 = 98765432;
    unsigned  num1 = 1111;
    extract_digits_in_order(vInt, num1);
    extract_digits_in_order(vInt2, num2);
    int maxlen = vInt.size() > vInt2.size() ? vInt.size() : vInt2.size();
    NEWLINE

    for (int i = 0; i < maxlen; ++i)
    {
        if (i < vInt.size())
            cout << vInt[i] << " ";
        else
        {
            for_each(vInt2.begin()+i, vInt2.end(), [](const auto& elem) {
                cout << elem << " ";
                });
            break;
        }
        if (i < vInt2.size())
            cout << vInt2[i] << " ";
        else
        {
            for_each(vInt.begin() + i, vInt.end(), [](const auto& elem) {
                cout << elem << " ";
                });
            break;
        }
    }

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

