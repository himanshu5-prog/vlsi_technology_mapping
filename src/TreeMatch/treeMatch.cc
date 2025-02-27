#include "treeMatch.hh"

TreeMatch ::
TreeMatch(){
    m_inputNetlist = nullptr;
    m_mappedNetlist = nullptr;
    m_debugMode = false;
}

TreeMatch ::
~TreeMatch() {
   for (auto &elem: m_validMapping){
       elem.second.clear();
       delete elem.first; // deleting logical gate
   }
   
   for (auto &elem: bestLibMapping){
       elem.second.leafNode.clear();
      // delete elem.first;
   }
   
   
   for (auto &elem: m_mapLogicalToMapped){
       delete elem.second; // deleting mapped gate
   }

   for (auto elem: m_mappedNetlistMap){
       elem.second.clear();
   }


}

void
TreeMatch :: init(){
    //Creating cell library
    LibraryCells lib;
    lib.init();

    if (m_debugMode){
        std::cout << "Printing library\n";
        lib.print();
        std::cout << "Finished printing library\n";
    }
    m_techCells = lib.getTechCell();
    //----------------------

    //Creating Netlist
    Netlist netlist;
    //netlist.createLogicAOI21Rotated();
    //netlist.createSimpleNor();
    //netlist.createSimpleCircuit();

    netlist.createNetlist_2();
    m_inputNetlist = netlist.getRootNetlist();
    assert(m_inputNetlist != nullptr);
    //-------------------------------------

    //Creating the hash for the netlist
    m_gateHashMap = createHashMap(m_inputNetlist);

    if (m_debugMode){
        std :: cout << "Gate hash created\n";
        printGateHash(m_gateHashMap);
        std :: cout << "Finished printing gate hash\n";
    }
    //-------------------------------------


}

void
TreeMatch :: doMatching(){
    GatePtr netListGate = (m_inputNetlist->getInputGate())[0];
    
    for(auto cell: m_techCells){

        if (m_debugMode){
            std :: cout << "doMatching :: techCell: " <<  getStringGateType (cell.name) << "\n";
        }
        GatePtr techCellGate = ((cell.root)->getInputGate())[0];
        traverseNetlist(cell, techCellGate, netListGate);
   }
}

void
TreeMatch :: traverseNetlist (TechCell techCellMap,  GatePtr techCell, GatePtr currentNode){

    std :: vector <GatePtr> v;

    if (m_debugMode){
        std :: cout << "traverseNetlist :: Pre-matchTree. tech cell name: " << getStringGateType (techCell->getGateType()) << ", current gate: " 
        << currentNode->getGateId() << ", gate type: "<< getStringGateType(currentNode->getGateType()) << "\n";
    }
    
    bool isMatch = matchTree(techCell, currentNode, v);

    if (m_debugMode){
        std :: cout << "traverseNetlist :: Matching cell id: " << currentNode->getGateId() << ", cell type: " << getStringGateType (currentNode->getGateType())
        << " with tech cell: " <<  getStringGateType( techCell->getGateType()) << ", matched: " << isMatch<<"\n";
    }
    MappedInfo m;
    if (isMatch){
        m.leafNode = v;
        m.mappedCellName = techCellMap.name;
        m.cost = techCellMap.cost;
        m_validMapping[currentNode].push_back(m);
    }

    if (minCost.find(currentNode) == minCost.end()){
        minCost[currentNode] = -1;
    }

    for(auto elem: currentNode->getInputGate()){
        if (elem->getGateType() == INPUT){
            continue;
        }
        traverseNetlist(techCellMap, techCell, elem);
    }
}

bool
TreeMatch :: matchTree (GatePtr techCell, GatePtr netlist, std :: vector<GatePtr> &leafNode){

    if (m_debugMode){
        std :: cout << "matchTree :: current techCell: " << techCell->getGateId() << ", " << getStringGateType(techCell->getGateType())<<
        ", netlist id: " << netlist->getGateId() << ", " << getStringGateType(netlist->getGateType()) << "\n";
    }

    if (techCell->getGateType() == INPUT){

        if (m_debugMode){
            std :: cout << "matchTree :: input pad found for techCell. netlist gate id: " << netlist->getGateId() << ", type: " 
            << getStringGateType (netlist->getGateType()) << "\n";
        }
        leafNode.push_back(netlist);
        return true;
    }
    
    if (techCell->getGateType() != netlist->getGateType()){

        if (m_debugMode){
            std :: cout << "matchTree :: Cell type is different. tech cell id: " << techCell->getGateId() << ", tech cell type: " 
            << getStringGateType(techCell->getGateType()) << ", netlist gate id: " << netlist->getGateId() << ", type: " << getStringGateType(netlist->getGateType()) << "\n";
        }

        return false;
    }

    assert (techCell->getGateType() == netlist->getGateType());
    assert (techCell->getInputCount() == netlist->getInputCount());

    std :: vector <GatePtr> t = techCell->getInputGate();
    std :: vector <GatePtr> n = netlist->getInputGate();
    if (techCell->getInputCount() == 1){
        return matchTree(t[0], n[0], leafNode);
    } else if (techCell->getInputCount() == 2){
        return matchTree(t[0],n[0], leafNode) && matchTree(t[1],n[1], leafNode);
    }

    assert (techCell->getInputCount() <= 2); 
    return false;
}

void
TreeMatch :: print(){
    
    //std :: cout << "Input Netlist: \n";
    //printGateHash(m_gateHashMap);
    std :: cout << "**********************************************************\n";
    std::cout << "valid mapping size: " << m_validMapping.size() << "\n";
    printValidMapping();

    std :: cout << "**********************************************************\n";
    std :: cout << "Minimum cost: " << m_minimumCost << "\n";
    //std :: cout << "Total mapped cells used (I/O not included): " << m_mappedNetlistGateCount << "\n";
    std :: cout << "Total gates in logical netlist (I/O not included): " << m_gateHashMap.size() - 1 << "\n";
    printMinCostMapping();

    std :: cout << "---------------------------------------------------------------\n";
    std :: cout << "Mapped Netlist gate count: " << m_mappedNetlistGateCount << "\n";
    printMappedNetlist();
}

void
TreeMatch :: printValidMapping(){
    GatePtr netlistGate;
    std :: vector <MappedInfo> m;
    
    for (auto iterator = m_validMapping.begin(); iterator != m_validMapping.end(); ++iterator){
        netlistGate = iterator->first;
        m = iterator -> second;
        std :: cout << "----------------------------------------------------\n";
        std :: cout << "Gate id: " << netlistGate->getGateId() << ", type: " << getStringGateType (netlistGate->getGateType()) << "\n";

        for (auto elem: m){
            std :: cout << "**********************************\n";
            std :: cout << "Tech map: " << getStringGateType(elem.mappedCellName) << "\n";
            std :: cout << "Cost: " << elem.cost << "\n";
            std :: cout << "Leaf node: \n";
            for (auto leaf: elem.leafNode){
                std :: cout << "Gate id: " << leaf->getGateId() << ", type: " << getStringGateType(leaf->getGateType()) << "\n";
            }

        }

    }
}

bool
TreeMatch :: allInputPadFanIn(GatePtr gate){
    std :: vector <GatePtr> fanin;
    fanin = gate->getInputGate();

    for (GatePtr elem: fanin){
        if (elem->getGateType() != INPUT){
            return false;
        }
    }

    return true;
}

int
TreeMatch :: getMinCost(){

    GatePtr netListGate = (m_inputNetlist->getInputGate())[0];

    return calculateMinCost(netListGate);

}

int
TreeMatch :: calculateMinCost(GatePtr gate){

    if (gate->getGateType() == INPUT){
        return 0;
    }
    std :: vector <MappedInfo> mappedInfo = m_validMapping[gate];

   
    int minimumCost = INT_MAX;
    int currentCost = 0;
    std :: vector<GatePtr> leafNodeVect;
    
    for (auto info : mappedInfo){
        currentCost = 0;
        leafNodeVect = info.leafNode;
        currentCost = info.cost;

        for (auto node: leafNodeVect){
            if (node->getGateType() == INPUT){
                continue;
            }
            
            if (minCost[node] != -1){
                currentCost += minCost[node];
                /*
                std :: cout << "Himanshu :: Using Hash map: gate: " << gate->getGateId() << ", gate type: " 
                << getStringGateType(gate->getGateType()) << " :: node id: " << node->getGateId() << ", node type: " << 
                getStringGateType(node->getGateType()) << ", cost of node: " << minCost[node] << ", tech lib cell: " << getStringGateType(info.mappedCellName)<< "\n"; 
                */
            } else {
                /*
                std :: cout << "Himanshu :: calling recursion. gate: " << gate->getGateId() << ", gate type: " <<
                getStringGateType(gate->getGateType()) << " :: node id: " << node->getGateId() << ", node type: " <<
                getStringGateType(node->getGateType()) << ", tech lob cell: " << getStringGateType(info.mappedCellName) <<"\n";
                */
                currentCost += calculateMinCost(node);
            }  
        }

        if (currentCost < minimumCost){
            minimumCost = currentCost;
            bestLibMapping[gate] = info;
        }

    }

    minCost[gate] = minimumCost ;
    std :: cout << "min cost for gate id: " << gate->getGateId() << ", type: " << getStringGateType( gate->getGateType()) << " is : " << minCost[gate] << "\n";
    
    return minimumCost;

}

void TreeMatch :: printMinCostMapping(){
    std :: cout << "Printing Best mapping\n";
    std :: map <GatePtr, MappedInfo> :: iterator itr;
    GatePtr currentGate;
    MappedInfo currentInfo;
    for (itr = bestLibMapping.begin(); itr != bestLibMapping.end(); ++itr) {
        currentGate = itr->first;
        currentInfo = itr->second;
        std:: cout << "**********************************************************************\n";
        std :: cout << "Gate id: " << currentGate->getGateId() << ", Gate type: " 
        << getStringGateType(currentGate->getGateType()) << ", mapped: " << getStringGateType (currentInfo.mappedCellName) << ", cost: " << currentInfo.cost << "\n";

        for (auto elem: currentInfo.leafNode){
            std :: cout << "Leaf node:: Gate id: " << elem->getGateId() << ", Gate type: " << getStringGateType(elem->getGateType()) << "\n";
        }
    }
}

void
TreeMatch :: performMinimumCostTreeCover(){
    m_minimumCost = getMinCost();
}

void
TreeMatch :: run(){
    //Perform initialization such as lib cell creation, netlist creation
    init();

    //Perform Tree Matching
    doMatching();

    // Minimum cost tree covering
    performMinimumCostTreeCover();

    //Create hashmap between logical and mapped netlist
    createMappedNetlist();

    //Create hashmap between mapped gate and input mapped gate
    createMappedNetlistMap();
}

void
TreeMatch :: createMappedNetlist(){
    GatePtr netListGate = (m_inputNetlist->getInputGate())[0];

    int mappedGateCount = 0;
    helperFunctionTraversal(netListGate, mappedGateCount);
    m_mappedNetlist = m_mapLogicalToMapped[netListGate];

    m_mappedNetlistGateCount = mappedGateCount;

}

void
TreeMatch :: helperFunctionTraversal( GatePtr gate, int& gateCount){

    if (gate->getGateType() == INPUT){
        GateType t = INPUT;
        GatePtr mappedGate = new Gate();
        mappedGate->setGateId(gate->getGateId());
        mappedGate->setGateType(t);
        m_mapLogicalToMapped[gate] = mappedGate;
        return;
    }
    //GateType mappedGatetype;
    MappedInfo info = bestLibMapping[gate];

    GateType gateType;
    gateType = info.mappedCellName;

    GatePtr mappedGate = new Gate();
    mappedGate->setGateId(gate->getGateId());
    mappedGate->setGateType(gateType);
    m_mapLogicalToMapped[gate] = mappedGate;
    ++gateCount;
        
    for (auto elem: info.leafNode){
        helperFunctionTraversal( elem, gateCount);
    }
}

void
TreeMatch :: createMappedNetlistMap(){
    GatePtr netListGate = (m_inputNetlist->getInputGate())[0];
    
    assert(m_mapLogicalToMapped.find(netListGate) != m_mapLogicalToMapped.end()); // gate should be in the hash-map
    helperFunctionCreateNetlistMap(netListGate);
}

void
TreeMatch :: helperFunctionCreateNetlistMap(GatePtr gate){

    if (gate->getGateType() == INPUT){
        return;
    }

    GatePtr map = m_mapLogicalToMapped[gate];
    MappedInfo info = bestLibMapping[gate];
    

    for (auto elem: info.leafNode){
        m_mappedNetlistMap[map].push_back(m_mapLogicalToMapped[elem]);
        helperFunctionCreateNetlistMap(elem);
    }
    
}
void
TreeMatch :: printMappedNetlist(){
    //GatePtr netListGate = (m_inputNetlist->getInputGate())[0];
    GatePtr netListGate = (m_inputNetlist->getInputGate())[0];

    assert(m_mapLogicalToMapped.find(netListGate) != m_mapLogicalToMapped.end()); // gate should be in the hash-map

    for (auto itr = m_mappedNetlistMap.begin(); itr != m_mappedNetlistMap.end(); ++itr){
        GatePtr gate = itr->first;
        std :: cout << "----------------------------------------------------\n";
        std :: cout << "Gate id: " << gate->getGateId() << ", type: " << getStringGateType(gate->getGateType()) << "\n";
        std :: cout << "Mapped gate: \n";
        for (auto elem: itr->second){
            std :: cout << "Gate id: " << elem->getGateId() << ", type: " << getStringGateType(elem->getGateType()) << "\n";
        }
    }

}