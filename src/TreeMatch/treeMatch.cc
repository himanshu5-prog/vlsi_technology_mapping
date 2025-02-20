#include "treeMatch.hh"

TreeMatch ::
TreeMatch(){
    m_inputNetlist = nullptr;
}

TreeMatch ::
~TreeMatch() {
    delete m_inputNetlist;

    for (auto elem: m_techCells){
        delete elem.root;
    }
}

void
TreeMatch :: init(){
    //Creating cell library
    LibraryCells lib;
    lib.init();
    //----------------------

    //Creating Netlist
    Netlist netlist;
    netlist.createNetlist_2();
    m_inputNetlist = netlist.getRootNetlist();
    //-------------------------------------

    //Creating the hash for the netlist
    m_gateHashMap = createHashMap(m_inputNetlist);
}