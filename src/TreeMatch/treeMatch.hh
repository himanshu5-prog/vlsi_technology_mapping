#ifndef __TREE_MATCH_HH__
#define __TREE_MATCH_HH__

#include <iostream>
#include "../LibraryCells/libraryCells.hh"
#include "../Netlist/netlist.hh"
#include <map>
#include <algorithm>

struct MappedInfo {
    GateType mappedCellName;
    std :: vector <GatePtr> leafNode;
    int cost;
};
class TreeMatch {
    std :: vector <TechCell> m_techCells;
    bool m_debugMode;
    GatePtr m_inputNetlist;
    std :: map <GatePtr, std :: vector <MappedInfo> > m_validMapping;
    std :: map <GatePtr, int> minCost;
    std :: map <GatePtr, MappedInfo> bestLibMapping;
    GateHashMap m_gateHashMap;
    int m_minimumCost;

    public:
        TreeMatch();
        ~TreeMatch();
        void init();
        void doMatching();

        bool matchTree (GatePtr techCell, GatePtr netlist, std :: vector <GatePtr> &leafNode);
        void traverseNetlist(TechCell techCellMap, GatePtr techCell, GatePtr netlist);
        void print();
        void printMapping();
        void printBestMapping();
        void performMinimumCostTreeCover();
        int getMinCost();
        int calculateMinCost(GatePtr gate);
        void traverseTree(GatePtr gate);
        inline void setDebugMode(){m_debugMode = true;}
        bool allInputPadFanIn(GatePtr gate);
        void run();

};

#endif