#ifndef __TREE_MATCH_HH__
#define __TREE_MATCH_HH__

#include <iostream>
#include "../LibraryCells/libraryCells.hh"
#include "../Netlist/netlist.hh"
#include <map>

class TreeMatch {
    std :: vector <TechCell> m_techCells;
    GatePtr m_inputNetlist;
    std :: map <GatePtr, std :: vector <GatePtr> > m_validMapping;
    std :: map <GatePtr, int> minCost;
    GateHashMap m_gateHashMap;

    public:
        TreeMatch();
        ~TreeMatch();
        void init();

};

#endif