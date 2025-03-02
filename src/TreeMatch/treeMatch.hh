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

    MappedInfo(){
        mappedCellName = NA;
        cost = 0;
    }
};
class TreeMatch {

    // Tech cell
    std :: vector <TechCell> m_techCells;

    // Debug mode
    bool m_debugMode;

    // Input netlist root
    GatePtr m_inputNetlist;

    // Valid mapping of each node in netlist
    std :: map <GatePtr, std :: vector <MappedInfo> > m_validMapping;

    // Minimum cost mapping for each node in netlist
    std :: map <GatePtr, int> m_minCostVect;

    // Best library mapping for each node in netlist
    std :: map <GatePtr, MappedInfo> m_bestLibMapping;

    // Mapping of gate to its input gate for logical netlist
    GateHashMap m_gateHashMap;

    // Overall minimum cost
    int m_minimumCost;


    // Mapped netlist

    // Root to mapped netlist
    GatePtr m_mappedNetlist;

    // Mapping mapped gate to input mapped gate
    std :: map<GatePtr, std::vector<GatePtr>> m_mappedNetlistMap;
    
    // Count of mapped gate
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