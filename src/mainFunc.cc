#include <iostream>
#include "Netlist/netlist.hh"
#include "LibraryCells/libraryCells.hh"

int main(){
  
    LibraryCells lib;

    lib.init();
    lib.print();

    //Netlist netlist;
    //netlist.createNetlist_2();
    //netlist.print();

    return 0;

}