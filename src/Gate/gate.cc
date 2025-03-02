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
    m_gateId = NA;
    m_gateId = -1;
    m_inputCount = 0;
    m_mapped = false;
}

Gate :: 
Gate(GateType g, int id, int ipCount, std :: vector <GatePtr> inGate){
    m_gateType = g;
    m_gateId = id;
    m_inputCount = ipCount;
    m_inputGate = inGate;

}

Gate :: ~Gate(){
}

void Gate :: printGate() const{
    std :: cout << "Printing Gate:\n";
    std :: cout << "GateType: " << getStringGateType(m_gateType) << "\n";
    std :: cout << "Gate id: " << m_gateId << "\n";
    

    if (m_inputCount > 0){
        std :: cout << "Input count: " << m_inputCount << "(" << m_inputGate.size() << ")"<< "\n";
        std :: cout << "Input gate ID: ";
        for (int elem: m_inputGateId){
            std :: cout << elem << " ";
        }
        std :: cout << "\n";
    }
    
    for (auto elem: m_inputGate){

       elem->printGate();
        
    }

}

// Get method
GateType Gate:: getGateType() const {
    return m_gateType;
}

int Gate :: getGateId() const {
    return m_gateId;
}


int Gate :: getInputCount() const{
    return m_inputCount;
}

std :: vector <GatePtr> 
Gate :: getInputGate(){
    return m_inputGate;
}

// set method
void Gate :: setGateType(GateType g){
    m_gateType = g;
}

void Gate :: setGateId (int id){
    m_gateId = id;
}


void Gate :: setInputCount (int c){
    m_inputCount = c;
}

void Gate :: setInputGate(std :: vector < GatePtr> v) {
    m_inputGate = v;
}

void Gate :: setMapped(){
    m_mapped = true;
}

bool Gate :: isMapped(){
    return m_mapped;
}