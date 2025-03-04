#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include "symtab.h"
//create Three Adress Code 
class Tac{

    private:
    std::string op, left, right, res;    
    public:
        Tac(){  //expressions
        //initialize the three address code
        this->op ="defaultOP";
        this->left = "defaultLeft";
        this->right = "defaultRight";
        this->res = "defaultRes";

        }
        Tac(std::string op, std::string left, std::string right, std::string res){
            this->op = op;
            this->left = left;
            this->right = right;
            this->res = res;
        }
        void printTac(){

            std::cout << res << " := " << left << " " << op << " "<< right << std::endl; 
        }
};

class BBlock    //statements,, if and while loops, methodDEc, classDec
{
private:
    /* data */
    std::string BlockName;
    std::vector<Tac> tacInstructions;
    Tac condition;
    BBlock *trueExit, *falseExit;

public:
    BBlock(/* args */): trueExit(nullptr), falseExit(nullptr){}
    ~BBlock(){}
};
