#include <iostream>
#include "csv.h"

int main() {
    std::string dataFile = "/Users/danbern/Documents/programming/CS320-Machine-Learning/data/00320uciedu/student-mat.csv";
    std::vector data = csv::parse(dataFile, ';');
    for (std::vector<std::string> row : data) {
        for(std::string value : row){
            std::cout<<value<<" ";
        }
        std::cout<<std::endl;
    }
    return 0;
}