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

int getQueenAttackValue(std::vector<int>& queenVector, int indexInQuestion, int valueAttempt = -1);

int main()
{
//Set up the data structures
    //A vector composed of integer arrays, vectors will need to be resized, but the int arrays will not
    //TODO: consider this more


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

//FindMostAttackedQueen (queenVector)
    //int currentMostQueen = TODO: assign default values

    //TODO: flesh out process to return most attacked queen value



//FindLeastAttackedValue (Takes: queen vector, indexInQuestion)
//Can this fail? What should I assign as a default value, how can it fail?
    //int leastAttackedValue = default currentIndex value

    //For loop, 0 - 8 for each possible value
        //int currentTryValue = getQueenAttackValue
        //If currentTryValue < leastAttacksValue
            //Assign currentTryValue to leastAttacksValue
        //Else -- Do Nothing

    //return leastAttackedValue;



int getQueenAttackValue(std::vector<int>& queenVector, int indexInQuestion, int valueAttempt)  //default valueAttempt is sentinel value that signals to check current index value
{
    int attacksCount = 0;
    int queenIndex; //The index that is currently being checked


    //This IF allows checking either the queen's current attack value, or probing before a value change
    if (valueAttempt != -1) { 
        queenIndex = valueAttempt;
    } 
    else {
        queenIndex = indexInQuestion;
    }


    //Now counting the number of attacks that occur
    for (int i = 1; i < 9; i++) {
        if (queenVector.at(i) == queenVector.at(queenIndex)) {
            attacksCount++; //This check has revealed that queen i and the queen at queenIndex are attacking each other by being in the same row.
            continue;
        }else if(abs(i - queenIndex) == abs(queenVector.at(i) - queenVector.at(queenIndex))){
            attacksCount++; //This check has revealed that the two queens are diagonal to each other, and are thus attacking each other.
            continue;
        }
    }

    return attacksCount;
}