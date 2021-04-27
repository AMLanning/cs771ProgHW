/* Avery Lanning
 * WSU ID: G958W553
 *
 * CS 771 - Artificial Intelligence
 * Title: 8 Queens Program
 * 
 * Description: This is my homework solving the 8 queens problem for my Artificial Intelligence course at Wichita State. All code is in one file - per class requirements.
 * Non-WSU Email: amlanning14@gmail.com
 */

//Remember to put declarations up here
#include <vector>
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>

int getLargestN1Queens(std::vector<int>& queenSet, std::vector<int*>& largestN1Queens);
int findMostAttackedQueen(std::vector<int>& queenVector);
void assignBestQueenRow(std::vector<int>& queenVector, int indexInQuestion);
int getQueenAttackValue(std::vector<int>& queenVector, int indexInQuestion, int valueAttempt = -1);

int main()
{
//Set up the data structures and variables
    std::vector<std::vector<int>> allQueenSets; //This vector will hold all of the initial states as their own vector
    std::string tmp;
    int numStates;

//Loading Initial States from the Input File
    std::ifstream inputFile("infile.txt");
    tmp = inputFile.get();
    numStates = std::stoi(tmp);//std::stoi(tmp);
    tmp = inputFile.get(); //Getting rid of the '\n'


    for (int i = 0; i < numStates; i++) {
        std::vector<int> singleQueenSet;
        singleQueenSet.push_back(-1); //This fills index 0 so that the index values can match the homework sheet

        for (int j = 0; j < 8; j++) {
            tmp = inputFile.get();

            singleQueenSet.insert(singleQueenSet.begin() + 1 + j, std::stoi(tmp)); //The +1 ensures that the state is stored in positions 1-8

            tmp = inputFile.get(); //Getting rid of the whitespace
        }

        allQueenSets.push_back(singleQueenSet);
    }

//Setting up the output file
    std::ofstream outfile("outfile.txt");


//Going through each queenSet and searching for the goal state
    for(int i = 0; i < numStates; i++) {
    std::vector<int> queenSet = allQueenSets.at(i);

    //Output the current queen state


    //Find the queens with n1 attacks, add their pointers to a vector
    std::vector<int*> queensWithN1;
    int n1 = getLargestN1Queens(queenSet, queensWithN1);

    //For each queen with n2, check its attack value
    if(n1 = 0) {
        outfile << "Success\n";    
        break;
    }
    }


//All Done!
    return 0;
}

void outputCurrentQueenState(std::vector<int> queenSet, std::ofstream& outfile)
{
    for(int i = 0; i < 9; i++) {
        outfile << queenSet.at(i);

        if(i != 8) {
            outfile << " ";
        }else {
            outfile << "\n";
        }
    }
}

bool checkIfFailure(int n1, std::vector<int> queenSet, std::vector<int*> largestN1Queens)
{

}

int getLargestN1Queens(std::vector<int>& queenSet, std::vector<int*>& largestN1Queens)
{
    int largestN1 = getQueenAttackValue(queenSet, 1);

    //Finding the largest n1 value
    for(int i = 2; i < 9; i++) {
        int tmp = getQueenAttackValue(queenSet, i);
        std::cout << tmp << "\n";
        if(tmp > largestN1) {//If true, a new largest has been found
            largestN1 = tmp;
        }
    }

    //Collecting All Queens with this largest n1 value
    for(int i = 1; i < 9; i++) {
        if(getQueenAttackValue(queenSet, i) == largestN1) {
            largestN1Queens.push_back(&(queenSet.at(1))); //Pushes a pointer to this position
        }
    }


    return largestN1;
}

int findMostAttackedQueen(std::vector<int>& queenVector) //Finds the index of the most attacked queen
{
    //The values
    int currentMostQueenIndex = 1; //Queen indexes start at 1 to match the assignment sheet
    int currentMostQueenValue = getQueenAttackValue(queenVector, currentMostQueenIndex);

    //Checking each queen's attack value
    for (int i = 2; i < 3; i++) { //Position 1 was checked to during initialization, it is not rechecked
        int tmpValue = getQueenAttackValue(queenVector, i);

        if (currentMostQueenValue < tmpValue) { //If any queen is more attacked than the current "favorite", it becomes the new "favorite"
            currentMostQueenIndex = i;
            currentMostQueenValue = tmpValue;
        }
    }

    return currentMostQueenIndex;
}

//I might have made a mistake, I should have written a function to find the value at which a queen is attacking the fewest queens
void assignBestQueenRow(std::vector<int>& queenVector, int indexInQuestion)
{
    int currentAttackValue = getQueenAttackValue(queenVector, indexInQuestion);
     
    //Testing each row number, and assigning whenever the current row number is lower.
        //Note that because this starts at the low end, any case of two rows having the same attack value will result in the lower row number
        //being the final state, as required in the HW description.
    for (int i = 1; i < 9; i++) {
        int tmpValue = getQueenAttackValue(queenVector, indexInQuestion, i); //Getting the attack value that would result from that value change

        //If the new value would reduce this queen's attack value, it is automatically assigned. The idea is the final state will be the lowest value
        if (tmpValue < currentAttackValue) {
            currentAttackValue = tmpValue;
            queenVector.at(indexInQuestion) = i;
        }
    }

    return; //The best value (with the least attacks) was assigned during execution
}


int getQueenAttackValue(std::vector<int>& queenVector, int indexInQuestion, int valueAttempt)  //default valueAttempt is sentinel value that signals to check current index value
{
    int attacksCount = 0;
    int queenIndex; //The index that is currently being checked


    //This IF allows checking either the queen's current attack value, or probing before a value change
    if (valueAttempt != -1) { 
        queenIndex = valueAttempt; //The function has been passed an attempt value to try
    } 
    else {
        queenIndex = indexInQuestion; //The function should look at the index's current value (default behavior)
    }


    //Now counting the number of attacks that occur
    for (int i = 1; i < 9; i++) {

    }

    return attacksCount;
}
