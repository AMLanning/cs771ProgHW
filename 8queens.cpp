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

int getLargestN1Queens(std::vector<int>& queenSet, std::vector<int>& largestN1QueenIndices);
int findMostAttackedQueen(std::vector<int>& queenVector);
void assignBestQueenRow(std::vector<int>& queenVector, int indexInQuestion);
int getQueenAttackValue(std::vector<int>& queenVector, int indexInQuestion, int valueAttempt = -1);

int main()
{
//Set up the data structures and variables
    std::vector<std::vector<int>> allQueenSets; //This vector will start with all of the initial states as their own vector
    std::string tmp;
    int numStates;
    std::vector<bool> resultVec;

//Test code for each function
    //findMostAttackedQueen Test Code
    //std::vector<int> tmp = { 0,-1,2,3,4,5,6,7,8 }; //The vector has 9 positions, 0 is unused, to match the homework's index values
    //allQueenSets.push_back(tmp);//([0,1,2,3,4,5,6,7]);
    //std::cout << "Most Attacked Queen: " << findMostAttackedQueen(allQueenSets.at(0)) << "\n";

//Loading Initial States from the Input File
    std::ifstream inputFile("infile.txt");
    tmp = inputFile.get();
    numStates = std::stoi(tmp);//std::stoi(tmp);
    tmp = inputFile.get(); //Getting rid of the '\n'


    for (int i = 0; i < numStates; i++) {
        std::vector<int> singleQueenSet;
        singleQueenSet.push_back(-1); //This fills position 1 so that the index values can match the homework sheet

        for (int j = 0; j < 8; j++) {
            tmp = inputFile.get();

            singleQueenSet.insert(singleQueenSet.begin() + 1 + j, std::stoi(tmp)); //The +1 ensures that the state is stored in positions 1-8

            tmp = inputFile.get(); //Getting rid of the whitespace
        }

        allQueenSets.push_back(singleQueenSet);
    }

//Searching for a Goal State
    //Loop through vector of queen initial states
        //Output Initial State
        //Loop until success/failure
            //Find queen with most attacks, if tie pick lowest index
            //Assign Value from function: FindLeastAttackedValue
                //If it fails, how do I handle failure?
            //Output current state of array
            
            //Check sucess/failure, if looping then neither
                //Have an if/if-else statement to output success/failure, use double '\n' to make a blank line after each run

    for(int i = 0; i < numStates; i++) {
        //Get the queenVec containing references to all queens at the current max n1 -- largest number of attacked queens
        std::vector<int> largestN1Queens;
        int n1 = getLargestN1Queens(allQueenSets.at(i), largestN1Queens);

        std::cout << "\nresult n1 "<< n1 << "\n";

        //Checking for success
        if(n1 == 0) {
            resultVec.push_back(true); //This has been solved
            break;
	}

        //Checking for failure
            //Check each queen with n1 if any have an n2 less than n1 continue, otherwise assign failure
        for(int j = 0; j < largestN1Queens.size(); j++) {
            int tmp = largestN1Queens.at(j); //The queen currently under consideration

            //If this particular queen is less than n1 then this is not a failure. It is only a failure when all queens have an attack value over n1
            if((getQueenAttackValue(allQueenSets.at(i), (allQueenSets.at(i)).at(tmp))) < n1) {
                break;
            }else if(j == (largestN1Queens.size() -1)) {
                resultVec.push_back(false); //This is unsolvable
            }
        }

        //After success/failure checks, perform changes
        assignBestQueenRow(allQueenSets.at(i), largestN1Queens.at(0));
    }





//Outputting the results
    std::ofstream outfile("outfile.txt");

    for (int i = 0; i < numStates; i++) {
        for (int j = 1; j < (allQueenSets.at(i)).size(); j++) {
            outfile << (allQueenSets.at(i)).at(j);

            if(j != (allQueenSets.at(i)).size() - 1) { //Spaces in between, newlines after the states is outputted
                outfile << " ";
            }else {
                outfile << "\n";
            }
        }
    }

    return 0;
}

int getLargestN1Queens(std::vector<int>& queenSet, std::vector<int>& largestN1QueenIndices)
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
            largestN1QueenIndices.push_back(i);
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

        //if (queenVector.at(i) == queenVector.at(queenIndex)) { //Same row case
        //    attacksCount++; //This check has revealed that queen i and the queen at queenIndex are attacking each other by being in the same row.
        //    continue;
        //}//else if(abs(i - queenIndex) == abs(queenVector.at(i) - queenVector.at(queenIndex))) { //Diagonal Case
        //    attacksCount++; //This check has revealed that the two queens are diagonal to each other, and are thus attacking each other.
        //    continue;
        //}
    }

    return attacksCount;
}
