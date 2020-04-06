
#include "main.h"

int main()
{

main: // label main

    std::cout << "Input your permutation:\n";
    std::getline(std::cin, permutationInput);

    std::stringstream stream(permutationInput);
    std::vector<int>* tempVector = new std::vector<int>;

    int n;
    while (stream >> n)
    {
        permutationLen += 1;
        tempVector->push_back(n);
    }

    int* permutation = new int[permutationLen];

    permutation = tempVector->data(); //Transfers data from vector to array

    tempVector->clear(); // Clears memory

    for (int i = 0; i < permutationLen; i++)
    {
        if (permutation[i] > permutationLen)
        {
            std::cout << "Permutation element is bigger than the length\n";
            goto main;
        }
    }

    std::cout << "The length of the permutation is " << permutationLen << "\n";

    int* inverse = new int[permutationLen];

    for (int i = 0; i < permutationLen;i++)
    {
        int pointingElement = permutation[i] - 1;

        inverse[pointingElement] = i + 1;
    }

    PrintPermutation(inverse);


    //Find Circles
    std::vector<int>* circles = FindCircles(permutation);

    std::cout << "Product of circles: " << std::endl;
    PrintCircles(circlesCount, circles);

    //Find Transpositions
    std::vector<int>* transpositions = FindTranspositions(circles);

    std::cout << "Transpositions: " << std::endl;
    PrintCircles(totalTranspositions, transpositions);


    if (totalTranspositions % 2 != 0)
    {
        std::cout << "The permutation is odd";
    }
    else
    {
        std::cout << "The permutation is even";
    }


    delete[] circles, transpositions;

    std::getchar();

    return 0;
}


std::vector<int>* FindCircles(int permutation[])
{

    std::vector<int>* tempCircles = new std::vector<int>[permutationLen];
    std::vector<int> alreadyUsed;

    permutationIndex = 1;
    circlesCount = 1;

    while (alreadyUsed.size() != permutationLen)
    {

        if (std::count(alreadyUsed.begin(), alreadyUsed.end(), permutationIndex))
        {
            if (std::count(tempCircles[circlesCount - 1].begin(), tempCircles[circlesCount - 1].end(), permutationIndex))
            {
                circlesCount += 1;
            }

            permutationIndex = rand() % permutationLen + 1;
            continue;
        }

        alreadyUsed.push_back(permutationIndex);

        tempCircles[circlesCount - 1].push_back(permutationIndex);

        permutationIndex = permutation[permutationIndex - 1];
    }

    return tempCircles;
}


void PrintCircles(int circlesCount, std::vector<int>* circles)
{
    for (int i = 0; i < circlesCount;i++)
    {
        std::cout << "(";

        for (size_t j = 0; j < circles[i].size();j++)
        {
            std::cout << circles[i].at(j) << " ";
        }

        std::cout << ") ";
    }

    std::cout << std::endl;
}


void PrintPermutation(int* permutation)
{
    for (int i = 0; i < permutationLen; i++)
    {
        std::cout << permutation[i] << " ";
    }

    std::cout << "\n";
}


std::vector<int>* FindTranspositions(std::vector<int>* circles)
{
    int* circleTranspositionsCount = new int[circlesCount];
    totalTranspositions = 0;

    //We find the number of transpositions
    for (int i = 0; i <= circlesCount - 1; i++)
    {
        int circleSize = circles[i].size();

        if (circleSize > 2)
        {
            circleTranspositionsCount[i] = circleSize - 1;
            totalTranspositions += circleSize - 1;
        }
        else if (circleSize == 2)
        {
            circleTranspositionsCount += 1;
            totalTranspositions += 1;
        }
    }


    std::vector<int>* transpositions = new std::vector<int>[totalTranspositions];

    int transpositionIndex = 0;
    for (int i = 0; i <= circlesCount - 1; i++)
    {
        for (int j = circles[i].size() - 1; j >= 1; j--)
        {
            transpositions[transpositionIndex].push_back(circles[i].at(0));
            transpositions[transpositionIndex].push_back(circles[i].at(j));
            transpositionIndex += 1;
        }
    }


    return transpositions;
}
