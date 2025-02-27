#ifndef __TREE_MATCH_HH__
#define __TREE_MATCH_HH__

#include <iostream>
#include "../LibraryCells/libraryCells.hh"
#include "../Netlist/netlist.hh"
#include <map>
#include <algorithm>
#include <queue>
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

    // Mapped netlist
    GatePtr m_mappedNetlist;
    std :: map<GatePtr, std::vector<GatePtr>> m_mappedNetlistMap;
    int m_mappedNetlistGateCount;

    // Mapping logical gate to mapped gate
    std :: map <GatePtr, GatePtr> m_mapLogicalToMapped; 

    public:
        // constructor and destructor
        TreeMatch();
        ~TreeMatch();
        //---------------------------

        void init();
        void run();
        
        // Tree matching
        void doMatching();
        bool matchTree (GatePtr techCell, GatePtr netlist, std :: vector <GatePtr> &leafNode);
        void traverseNetlist(TechCell techCellMap, GatePtr techCell, GatePtr netlist);
        //--------------------------------------------
        //Print functions
        void print();
        void printValidMapping();
        void printMinCostMapping();
        //------------------------------
        // Minimum cost tree-covering----------
        void performMinimumCostTreeCover();
        int getMinCost();
        int calculateMinCost(GatePtr gate);
        //-------------------------------------
        //void traverseTree(GatePtr gate);
        // Helper function------------------------------
        inline void setDebugMode(){m_debugMode = true;}
        bool allInputPadFanIn(GatePtr gate);
        //---------------------------------------------
        // Creating mapped netlist
        void createMappedNetlist();
        void helperFunctionTraversal( GatePtr gate, int& count);

        //Printing mapped netlist
        void printMappedNetlist();
        void traverseTreePrint(GatePtr gate);
        void createMappedNetlistMap();
        void helperFunctionCreateNetlistMap(GatePtr gate);
        //---------------------------------------------
        
        

};

#endif