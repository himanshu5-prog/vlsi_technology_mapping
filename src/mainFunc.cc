#include <iostream>
#include "TreeMatch/treeMatch.hh"
int main(){
  
    TreeMatch techMap;

    techMap.init();
    techMap.doMatching();
    techMap.print();
    
    return 0;

}