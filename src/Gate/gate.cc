#include "gate.hh"
//typedef std::shared_ptr<Gate> GatePtr;
typedef Gate* GatePtr;
std :: string getStringGateType(GateType g){

    std :: string strGate = "NA";
    switch (g){
        case INPUT: 
            strGate = "INPUT";
            break;
        case OUTPUT:
            strGate = "OUTPUT";
            break;
        case NOT:
            strGate = "NOT";
            break;
        case AND2:
            strGate = "AND2";
            break;
        case OR2:
            strGate = "OR2";
            break;
        case NOR2:
            strGate = "NOR2";
            break;
        case AOI21:
            strGate = "AOI21";
            break;
        case AOI21_ROTATED:
            strGate = "AOI21_ROTATED";
            break;
        case NAND2:
            strGate = "NAND2";
            break;
        case AOI22:
            strGate = "AOI22";
            break;
        default:
            strGate = "NA";
    }

    return strGate;
}

Gate ::
Gate (){
    gateType = NA;
    gateId = -1;
    inputCount = 0;
    m_mapped = false;
}

Gate :: 
Gate(GateType g, int id, GatePtr outGate, int ipCount, std :: vector <GatePtr> inGate){
    gateType = g;
    gateId = id;
    inputCount = ipCount;
    inputGate = inGate;

}

Gate :: ~Gate(){
    /*
    for (auto elem: inputGate){
        delete elem;
    }
    */
}

void Gate :: printGate(){
    std :: cout << "Printing Gate:\n";
    std :: cout << "GateType: " << getStringGateType(gateType) << "\n";
    std :: cout << "Gate id: " << gateId << "\n";
    

    if (inputCount > 0){
        std :: cout << "Input count: " << inputCount << "(" << inputGate.size() << ")"<< "\n";
        std :: cout << "Input gate ID: ";
        for (int elem: inputGateId){
            std :: cout << elem << " ";
        }
        std :: cout << "\n";
    }
    

    for (auto elem: inputGate){

       elem->printGate();
        
    }

}

// Get method
GateType Gate:: getGateType(){
    return gateType;
}

int Gate :: getGateId(){
    return gateId;
}


int Gate :: getInputCount(){
    return inputCount;
}

std :: vector <GatePtr> 
Gate :: getInputGate(){
    return inputGate;
}

// set method
void Gate :: setGateType(GateType g){
    gateType = g;
}

void Gate :: setGateId (int id){
    gateId = id;
}


void Gate :: setInputCount (int c){
    inputCount = c;
}

void Gate :: setInputGate(std :: vector < GatePtr> v) {
    inputGate = v;
}