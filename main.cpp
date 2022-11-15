
#include <iostream>
#include <vector>

#define INF INT_MAX

using namespace std;

typedef vector<vector<int>> MTRX;

MTRX getCostMatrix(vector<string>, int);

vector<int> getSolArray(MTRX);

int dispSol(vector<int>, vector<string>, int);

void wrapText(string, int);

string getTillChar(string &, char);

int main()
{

    string test = "Jackie Tom loves to cook";
    int lenTest = 10;

    wrapText(test, lenTest);

    return 0;
}

MTRX getCostMatrix(vector<string> listOfWords, int lineLength)
{
    int size = listOfWords.size() + 1;
    int tempCost;

    MTRX totalcost(size, vector<int>(size, INF));

    for (int i = 1; i < size; i++)
    {
        tempCost = lineLength;

        for (int j = i; j < size - 1; j++)
        {
            if (i == j)
                tempCost -= listOfWords[j - 1].size();
            else
                tempCost -= (listOfWords[j - 1].size() + 1);

            if (tempCost < 0)
                totalcost[i][j] = INF;
            else
                totalcost[i][j] = (tempCost * tempCost);

        }
    }

    return totalcost;
}

vector<int> getSolArray(MTRX linecost)
{
    int size = linecost.size();

    int totalCost[size];

    vector<int> sol(size);

    for (int i = 0; i < size; i++)
    {
        if (i == 0)
            totalCost[i] = 0;
        else
            totalCost[i] = INF;
    }

    int temp;

    for (int j = 1; j < size ; j++)
    {
        for (int i = 1; i <= j; i++)
        {   
            if(linecost[i][j] != INF)
            {
                temp = totalCost[i - 1] + linecost[i][j];

                if (temp <= totalCost[j])
                {
                    totalCost[j] = temp;
                    sol[j] = i;
                    cout << totalCost[j] << "\t";
                    cout << sol[j] << endl;
                }
            }
        }
    }

    return sol;
}

int dispSol(vector<int> sol, vector<string> words, int size)
{
    int k;

    if (sol[size] == 1)
        k = 1;
    else
        k = dispSol(sol, words, sol[size - 1]) + 1;

    cout << endl << "Line number " << k << ": ";

    for(int i = sol[size]; i < size; i++)
        cout << " " << words[i];

    return k;
}

void wrapText(string words, int linelength)
{
    vector<string> Words;

    char space = ' ';

    for (int i = 0; i < words.size() + 1; i++)
    {
        Words.push_back(getTillChar(words, space));
    }
    
    MTRX cost = getCostMatrix(Words, linelength);

    vector<int> sol = getSolArray(cost);

    dispSol(sol, Words, Words.size());
}

string getTillChar(string &word, char c)
{
    string result = "";

    int i;

    for (i = 0; i < word.size() && word[i] != c; i++)
    {
        result += word[i];
    }
    if (i != word.size())
        word = word.substr(i + 1, word.size() - 1);
    else
    {
        result = word;
        word = "";
    }
    return result;
}