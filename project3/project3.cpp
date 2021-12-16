//implementation of own code
#include <iostream>
#include <string>
#include <cassert> //assert (some boolean expression)
#include "grid.h"

using namespace std;

//global functions for readability implemented below
//convert char to an integer
int charToInt(char ch) {
    return (static_cast<int>(ch)) - 48;
}

void changeDirection(char turn, char& direction) { //change the direction vector when ta turn is initiated.
    //case 1 - when a left turn is initiated.
    if (turn == 'l' || turn == 'L') { //mind both upper and lower cases of left
        if (direction == 'N' || direction == 'n') {
            direction = 'W';
        }
        else if (direction == 'W' || direction == 'w') {
            direction = 'S';
        }
        else if (direction == 'S' || direction == 's') {
            direction = 'E';
        }
        else if (direction == 'E' || direction == 'e') {
            direction = 'N';
        }
    }

    //case 2 - when a right turn is initiated
    else if (turn == 'R' || turn == 'r') {
        if (direction == 'N' || direction == 'n') {
            direction = 'E';
        }
        else if (direction == 'W' || direction == 'w') {
            direction = 'N';
        }
        else if (direction == 'S' || direction == 's') {
            direction = 'W';
        }
        else if (direction == 'E' || direction == 'e') {
            direction = 'S';
        }
        else {
        }
    }
}

//determine if direction vector input is a valid input
bool validDirection(char dir) {
    if (!(dir == 'w' || dir == 'W' || dir == 'N' || dir == 'n' || dir == 'N' || dir == 'e' || dir == 'E' || dir == 's' || dir == 'S')) {
        return false;
    }
    return true;
}

//determine if a given point is out of bounds
bool outOfBounds(int r, int c) {
    if (r < 1 || r > getRows() || c < 1 || c > getCols()) {
        return true;
    }
    return false;
} 


//MAJOR REQUIRED FUNCTIONS IMPLEMENTED BELOW
//determine if a given plan is valid
bool hasCorrectForm(string plan) { //has a default bool false
    
    unsigned int index = 0;

    do {
        //case 0: when there is no portion
        if (plan == "") {
            return true;
        }

        //Case 1: when the portion is 0
        //if (plan.at(index) == '0') {
        //    index++;
        //}
        
        //Case 2: when the current portion is a number between 0 and 9
        else if (plan.at(index) >= '0' && plan.at(index) <= '9') {
            index++; //move on to the next index but stay in the case
            //hedge against overflow
            if (index >= plan.size()) {
                return false;
            }

            //case 2a: the next letter in the portion is a turn letter
            if (plan.at(index) == 'l' || plan.at(index) == 'L' || plan.at(index) == 'r' || plan.at(index) == 'R') {
                index++; //the portion is valid; redo the loop and move on to the next index
            }

            //case 2b: the next letter is still a number:
            else if (plan.at(index) <= '9' && plan.at(index) >= '0') {
                index++; //move on to the next index
                //hedge against overflow
                if (index >= plan.size()) {
                    return false;
                }

                //case 2b-a: the next letter is a turn letter
                if (plan.at(index) == 'l' || plan.at(index) == 'L' || plan.at(index) == 'r' || plan.at(index) == 'R') {
                    index++; //the portion is valid; redo te loop and move on to the next index
                }

                //case 2b-b  - the next letter is other letters or numbers
                else {
                    return false; //straight up invalid
                }
            }

            //case 2c - the next letter is other letters
            else {
                return false; //straght up invalid;
            }
        }

        //Case 3: when the portion is a direction vecotr
        else if (plan.at(index) == 'l' || plan.at(index) == 'L' || plan.at(index) == 'r' || plan.at(index) == 'R') {
            index++; //valid; move on to the next portion
        }

        //case 4: the beginning of the portion is other letters
        else {
            return false; //straight up invalid
        }
    } while (index < plan.length()); //continue doing the loop until the index number is over max

    return true; //if the function makes this far, give them a true value
}

//Calculate the max 1D distance
int determineSafeDistance(int r, int c, char dir, int maxSteps) {
    int currentStep = 0; //initialize a currentstep variable

    //ELIMINATE RIDICULOUS CASES FIRST
    //Case 1: when the starting position is invalid
    if (outOfBounds(r, c) || isWall(r, c)) {
        return -1;
    }

    //Case 2: invalid direction vector input
    else if (!validDirection(dir)) {
        return -1;
    }

    //Case 3: when maxstep is negative
    else if (maxSteps < 0) {
        return -1;
    }

    //move on to the acceptable cases
    else {
        //determine the direction and execute by cases
        if (dir == 'N' || dir == 'n') { //North
            for (int k = 0; k < maxSteps; k++) {
                r--; //step
                currentStep++;

                if (outOfBounds(r, c) == true || isWall(r, c) == true) { //make sure that the updated coordinates are valid
                    return currentStep - 1; //if it is, return the maximum steps
                }
            }
        }
        else if (dir == 'W' || dir == 'w') {
            for (int k = 0; k < maxSteps; k++) {
                c--;
                currentStep++;

                if (outOfBounds(r, c) == true || isWall(r, c) == true){
                    return currentStep - 1;
                }
            }
        }

        else if (dir == 'E' || dir == 'e') {

            for (int k = 0; k < maxSteps; k++) {
                c++;
                currentStep++;

                if (outOfBounds(r, c) == true || isWall(r, c) == true) {
                    return currentStep - 1;
                }
            }
        }

        else if (dir == 'S' || dir == 's') {
            for (int k = 0; k < maxSteps; k++) {
                r++;
                currentStep++;

                if (outOfBounds(r, c) == true || isWall(r, c) == true) {
                    return currentStep - 1;
                }
            }
        }

        //anything else is also invalid
        else {
            return -1;
        }
    }
    return maxSteps; //if nothing happens, return maxSteps
}

int obeyPlan(int sr, int sc, int er, int ec, char dir, string plan, int& nsteps) {
    //eliminate the invalid circumstances first
        //type 1A error - out of bounds or wall
    if (outOfBounds(sr, sc) || outOfBounds(er, ec) || isWall(sr, sc) || isWall(er, ec)) {
        return 2;
    }

        //type 1B error : other parameters are false
    if (!validDirection(dir) || !hasCorrectForm(plan)) {
        return 2;
    }

    //calculate where the final destination according to the plan is
    int numberOfSteps = 0;
    int moves = 0; //initialized moves here
    unsigned int index = 0;

    //copy a portion into moves
    if (plan.size() == 0){
        if (sr == er && sc == ec) {
            nsteps = 0;
            return 0;
        }
        else {
            nsteps = 0;
            return 1;
        }
    }

    while (index < plan.size()) {
        char currentDigit = plan.at(index);
        //cerr << "Current Digit: " << currentDigit << endl;
        char nextDigit = plan.at(index + 1);
        //cerr << "Next digit: " << nextDigit << endl;

        //if (currentDigit == '0') { //if the current digit is 0
            //case 1: individual portion
            //moves = 0;
            //index++;
        //}

        if (currentDigit >= '0' && currentDigit <= '9') { //include the case where a two-digit number is a plan portion

            //case 3a. if there is only one digit - suspect - nsteps NEEDS TO be updated
            if ((index + 1) < plan.length()) {
                if (nextDigit == 'l' || nextDigit == 'L' || nextDigit == 'R' || nextDigit == 'r') {
                    int proposedmoves = charToInt(currentDigit);
                    //cerr << "Proposed moves: " << proposedmoves << endl;

                    moves = determineSafeDistance(sr, sc, dir, proposedmoves); //get the max number of moves the car can go in this single direction

                    //cerr << "maximum number of legal moves: " << moves << endl;

                    //somehow after all the tests are passed the code is directed into this condition
                    if (moves != proposedmoves) { //Error 3: when the plan bumps into something or out of bounds
                        numberOfSteps += moves;
                        nsteps = numberOfSteps; //return the max number of viable steps

                        //cerr << "Updated nsteps: " << nsteps << endl;
                        return 3;
                    }
                    index++;
                }

                //case 3b. if there is another digit
                else if (nextDigit >= '0' && nextDigit <= '9') {
                    int first = charToInt(currentDigit);
                    int second = charToInt(nextDigit);
                    int portionmove = first * 10 + second;

                    moves = determineSafeDistance(sr, sc, dir, portionmove); //get the max number of moves the car can go in this single direction

                    if (moves != portionmove) { //Error 3: when the plan bumps into something or out of bounds
                        numberOfSteps += moves; //get the max number of viable steps
                        nsteps = numberOfSteps; //return max
                        return 3;
                    }

                    index += 2; //since we have already look over the next Digit, we skip it
                }
            }

            else {
                return 2;
            }

            //we got the number of steps. Now change the coordinates.
            if (dir == 'N' || dir == 'n') {
                sr -= moves; //move down rows
                //cerr << sr << " " << sc << endl;
                numberOfSteps += moves; //we add the number of steps by moves because moves is the safe distance
            }

            else if (dir == 'E' || dir == 'e') {
                sc += moves;
                //cerr << sr << " " << sc << endl;
                numberOfSteps += moves;
            }

            else if (dir == 'S' || dir == 's') {
                sr += moves;
                // cerr << sr << " " << sc << endl;
                numberOfSteps += moves;
            }

            else if (dir == 'W' || dir == 'w') {
                sc -= moves;
                //cerr << sr << " " << sc << endl;
                numberOfSteps += moves;
            }
        }

        if (currentDigit == 'l' || currentDigit == 'L' || currentDigit == 'R' || currentDigit == 'r') {
            //use the new function changeDirection
            moves = 0; //reset moves to avoid troubles
            changeDirection(plan.at(index), dir); //FIXME - this function will change the variable dir. Be careful by couting dir another time
            index++;
            //cerr << "New direction: " << dir << endl;
        }

        if (index == plan.size() - 1) {
            nsteps = numberOfSteps;
            //now, the starting point has been converted to the end point
            //compare the end point with the desired end point
            //cerr << sr << " " << sc << endl;
            //cerr << er << " " << ec << endl;

            if (sr == er && sc == ec) {
                //cout << "compared." << endl;
                return 0;
            }

            if (!(sr == er && sc == ec)) {
                //cout << "failed." << endl;
                return 1;
            }
            else {
                return 2;
            }
        }
    }
    return 2;
}

int main() {
    setSize(12, 13);
    setWall(1, 8);
    setWall(2, 2);
    setWall(3, 5);
    setWall(4, 4);
    setWall(5, 3);
    setWall(5, 4);
    setWall(6, 7);
    setWall(6, 8);
    setWall(7, 4);
    setWall(8, 4);
    setWall(9, 4);
    setWall(10, 4);
    draw(6, 1, 9, 6);
    cerr << determineSafeDistance(5, 13, 'w', 13) << endl;
    
    int len;
    len = -999;
    assert(obeyPlan(2, 13, 3, 4, 'S', "R10L2R2L2l1l3r2L", len) == 0 && len == 22);
    len = -999;
    assert(obeyPlan(2, 13, 3, 4, 'S', "R10L", len) == 1 && len == 10);
    cerr << obeyPlan(2, 13, 3, 4, 'S', "R10L2R2L2l1l3r2L", len) << endl;
    cerr << len << endl;
    cerr << obeyPlan(2, 13, 3, 4, 'S', "R11R3R", len) << endl;
    cerr << len << endl;
    len = -999;
    assert(obeyPlan(2, 13, 2, 13, 'S', "000000000000", len) == 2 && len == -999);
    len = -999;
    assert(obeyPlan(2, 13, 2, 13, 'S', "00lr", len) == 0 && len == 0);
    
    setSize(3, 4);
    setWall(1, 4);
    setWall(2, 2);
    setWall(3, 2);
    draw(3, 1, 3, 4);

    assert((determineSafeDistance(-1, 1, 'e', 2) == -1));
    assert((determineSafeDistance(1, 1, 'e', -8797) == -1));
    assert((determineSafeDistance(1, 1, 'O', 2) == -1));
    assert((determineSafeDistance(1, 1, 'e', 2) == 2));
    assert((determineSafeDistance(1, 1, 'S', 5) == 2));
    assert((determineSafeDistance(3, 4, 'n', 5) == 1));
    assert((determineSafeDistance(3, 4, 'w', 3) == 1));
    
    assert(hasCorrectForm(""));
    assert(hasCorrectForm("2R1r"));
    assert(!hasCorrectForm("1Lx"));
    assert(!hasCorrectForm("000000000000000"));
    assert(hasCorrectForm("00l1R3L"));
    assert(!hasCorrectForm("9RRRRRR3100"));
    assert(!hasCorrectForm("LR999"));
    assert(!hasCorrectForm("LR99"));
    assert(hasCorrectForm("LR88R"));
    assert(!hasCorrectForm("r10L9*"));
    assert(!hasCorrectForm("RL7900R1l"));
    assert(hasCorrectForm("LRLLRLRLLRRLLLRLLRLllrLlrlR"));
    assert(!hasCorrectForm("* (^ &*%(*&(&("));
    
    len = -999;  // so we can detect whether obeyPlan sets len
    assert(obeyPlan(3, 1, 3, 4, 'S', "LL2R2r2L1R", len) == 0 && len == 7);
    len = -999;  // so we can detect whether obeyPlan sets len
    assert(obeyPlan(3, 1, 3, 4, 'N', "1Lx", len) == 2 && len == -999);
    len = -999;  // so we can detect whether obeyPlan sets len
    assert(obeyPlan(2, 4, 1, 1, 'w', "3R1L", len) == 3 && len == 1);
    cerr << "All tests succeeded" << endl;
    len = -999;
    assert(obeyPlan(3, 1, 3, 4, 'N', "2RLR2R2L1L", len) == 0 || len == 7); //either the turn letter is wrong or the last digit
    len = -999;
    assert((obeyPlan(1, 1, 3, 4, 'E', "2R2L1L", len) == 0 && len == 5));
    len = -999; //test this wall bumper
    assert(obeyPlan(3, 1, 3, 4, 'n', "2R01r2L", len) == 3 && len == 3);
    cerr << "The max distance is " << len << endl;

    len = -999;
    cerr << obeyPlan(1, 1, 3, 4, 'N', "R4R2L", len) << endl;
    cerr << len << endl;
    len = -999;  // so we can detect whether obeyPlan sets len
    assert(obeyPlan(3, 1, 3, 4, 'S', "LL2R2r2L1R", len) == 0 && len == 7);
    len = -999;
    assert(obeyPlan(3, 1, 3, 4, 'N', "1Lx", len) == 2 && len == -999);
    len = -999;  // so we can detect whether obeyPlan sets len
    assert(obeyPlan(2, 4, 1, 1, 'w', "3R1L", len) == 3 && len == 1);
    len = -999;
    assert(obeyPlan(2, 4, 1, 1, 'w', "", len) == 1 && len == 0);
    assert(obeyPlan(2, 4, 2, 4, 'w', "", len) == 0 && len == 0);
    cerr << "All tests succeeded!" << endl;
}
