/* Avery Lanning
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

int findMostAttackedQueen(std::vector<int>& queenVector);
void assignBestQueenRow(std::vector<int>& queenVector, int indexInQuestion);
int getQueenAttackValue(std::vector<int>& queenVector, int indexInQuestion, int valueAttempt = -1);

int main()
{
//Set up the data structures
    std::vector<std::vector<int>> allQueenSets; //This vector will start with all of the initial states as their own vector


//Loading Initial States from the Input File
    //Open file
    //For each line:
        //Get each queen state value, place it in the corresponding data structure


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

    return 0;
}

int findMostAttackedQueen(std::vector<int>& queenVector) //Finds the index of the most attacked queen
{
    //The values
    int currentMostQueenIndex = 1; //Queen indexes start at 1 to match the assignment sheet
    int currentMostQueenValue = getQueenAttackValue(queenVector, currentMostQueenIndex);


    //Checking each queen's attack value
    for (int i = 2; i < 9; i++) { //Position 1 was checked to during initialization, it is not rechecked
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
        if (queenVector.at(i) == queenVector.at(queenIndex)) { //Same row case
            attacksCount++; //This check has revealed that queen i and the queen at queenIndex are attacking each other by being in the same row.
            continue;
        }else if(abs(i - queenIndex) == abs(queenVector.at(i) - queenVector.at(queenIndex))) { //Diagonal Case
            attacksCount++; //This check has revealed that the two queens are diagonal to each other, and are thus attacking each other.
            continue;
        }
    }

    return attacksCount;
}