#include "treeMatch.hh"

TreeMatch ::
TreeMatch(){
    m_inputNetlist = nullptr;
}

TreeMatch ::
~TreeMatch() {
     m_inputNetlist = nullptr;
    /*
    for (auto elem: m_techCells){
        delete elem.root;
    }
    */
}

void
TreeMatch :: init(){
    //Creating cell library
    LibraryCells lib;
    lib.init();
    m_techCells = lib.getTechCell();
    //----------------------

    //Creating Netlist
    Netlist netlist;
    netlist.createNetlist_2();
    //netlist.createSimpleCircuit();
    m_inputNetlist = netlist.getRootNetlist();
    //-------------------------------------

    //Creating the hash for the netlist
    m_gateHashMap = createHashMap(m_inputNetlist);
}

void
TreeMatch :: doMatching(){

    
    
   
    GatePtr netListGate = (m_inputNetlist->getInputGate())[0];
    
    for(auto cell: m_techCells){
        std :: cout << "doMatching :: techCell: " <<  getStringGateType (cell.name) << "\n";
        GatePtr techCellGate = ((cell.root)->getInputGate())[0];
        traverseNetlist(cell, techCellGate, netListGate);
   }
}

void
TreeMatch :: traverseNetlist (TechCell techCellMap,  GatePtr techCell, GatePtr currentNode){

    std :: vector <GatePtr> v;
    std :: cout << "traverseNetlist :: Pre-matchTree. tech cell name: " << getStringGateType (techCell->getGateType()) << ", current gate: " 
    << currentNode->getGateId() << ", gate type: "<< getStringGateType(currentNode->getGateType()) << "\n";

    
    bool isMatch = matchTree(techCell, currentNode, v);
    std :: cout << "traverseNetlist :: Matching cell id: " << currentNode->getGateId() << ", cell type: " << getStringGateType (currentNode->getGateType())
    << " with tech cell: " <<  getStringGateType( techCell->getGateType()) << ", matched: " << isMatch<<"\n";
    MappedInfo m;
    if (isMatch){
        m.leafNode = v;
        m.mappedCellName = techCellMap.name;
        m.cost = techCellMap.cost;
        m_validMapping[currentNode].push_back(m);
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

    std :: cout << "matchTree :: current techCell: " << techCell->getGateId() << ", " << getStringGateType(techCell->getGateType())<<
    ", netlist id: " << netlist->getGateId() << ", " << getStringGateType(netlist->getGateType()) << "\n";
    if (techCell->getGateType() == INPUT){
        std :: cout << "matchTree :: input pad found for techCell. netlist gate id: " << netlist->getGateId() << ", type: " 
        << getStringGateType (netlist->getGateType()) << "\n";
        leafNode.push_back(netlist);
        return true;
    }
    
    if (techCell->getGateType() != netlist->getGateType()){
        std :: cout << "matchTree :: Cell type is different. tech cell id: " << techCell->getGateId() << ", tech cell type: " 
        << getStringGateType(techCell->getGateType()) << ", netlist gate id: " << netlist->getGateId() << ", type: " << getStringGateType(netlist->getGateType()) << "\n";
        return false;
    }

    assert (techCell->getGateType() == netlist->getGateType());
    assert (techCell->getInputCount() == netlist->getInputCount());

    std :: vector <GatePtr> t = techCell->getInputGate();
    std :: vector <GatePtr> n = netlist->getInputGate();
    if (techCell->getInputCount() == 1){
        return matchTree(t[0], n[0], leafNode);
    } else if (techCell->getInputCount() == 2){
        return matchTree(t[0],n[0], leafNode) & matchTree(t[1],n[1], leafNode);
    }

    assert (techCell->getInputCount() <= 2); 
    return false;
}

void
TreeMatch :: print(){
    std::cout << "valid mapping size: " << m_validMapping.size() << "\n";
    printMapping();
    //assert (m_inputNetlist != nullptr);
    //m_inputNetlist->printGate();
}

void
TreeMatch :: printMapping(){
    auto iterator = m_validMapping.begin();
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