#ifndef __TREE_MATCH_HH__
#define __TREE_MATCH_HH__

#include <iostream>
#include "../LibraryCells/libraryCells.hh"
#include "../Netlist/netlist.hh"
#include <map>

struct MappedInfo {
    GateType mappedCellName;
    std :: vector <GatePtr> leafNode;
    int cost;
};
class TreeMatch {
    std :: vector <TechCell> m_techCells;
    GatePtr m_inputNetlist;
    std :: map <GatePtr, std :: vector <MappedInfo> > m_validMapping;
    std :: map <GatePtr, int> minCost;
    GateHashMap m_gateHashMap;
    int getCost (TechCell techCell);

    public:
        TreeMatch();
        ~TreeMatch();
        void init();
        void doMatching();

        bool matchTree (GatePtr techCell, GatePtr netlist, std :: vector <GatePtr> &leafNode);
        void traverseNetlist(TechCell techCellMap, GatePtr techCell, GatePtr netlist);
        void print();
        void printMapping();

};

#endif