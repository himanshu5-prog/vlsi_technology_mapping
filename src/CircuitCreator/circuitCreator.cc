#include "circuitCreator.hh"

GatePtr createPrimitiveNotGate(int id) {
    GatePtr notGate = new Gate();
    notGate->setGateId(id);
    notGate->setGateType(NOT);
    notGate->setInputCount(1);

    return notGate;
}

GatePtr createPrimitiveNandGate (int id) {
    GatePtr nandGate = new Gate();

    nandGate->setGateId(id);
    nandGate->setGateType(NAND2);
    nandGate->setInputCount(2);

    return nandGate;
}

GatePtr createPrimitivePad (int id, GateType type){
    GatePtr pad = new Gate();

    pad->setGateId(id);
    pad->setGateType(type);
    
    if (type == OUTPUT){
        pad->setInputCount(1);
    } else {
        pad->setInputCount(0);
    }

    return pad;
}

bool checkNotGate( GatePtr gate){

    if (gate->getGateType() != NOT){
        return false;
    }

    if (gate->getInputCount() == 1){
        return true;
    }

    return false;
}

bool checkNandGate(GatePtr gate) {

    if (gate->getGateType() != NAND2){
        return false;
    }

    if (gate->getInputCount() != 2){
        return false;
    }

    if (gate->getInputCount() == 2){
        std::vector <GatePtr> v = gate->getInputGate();

        assert (v.size() == 2);

        if (v[0] == v[1]){
            return false;
        }
    }

    return true;
}

bool checkOutputPad(GatePtr gate){

    if (gate->getGateType() != OUTPUT){
        return false;
    }

    if (gate->getInputCount() == 1){
        return true;
    }

    return false;
}

bool checkInputPad(GatePtr gate){

    if (gate->getGateType() != INPUT){
        std :: cerr << "Wrong gate type. Expecting INPUT but received" << getStringGateType(gate->getGateType()) << "\n";
        return false;
    }

    if (gate->getInputCount() == 0){
        return true;
    }

    return false;
}

bool checkGate (GatePtr gate){
    if (gate->getGateType() == INPUT){
        return checkInputPad(gate);

    } else if (gate->getGateType() == OUTPUT){
        return checkOutputPad(gate);

    } else if (gate->getGateType() == NOT){
        return checkNotGate(gate);

    } else if (gate->getGateType() == NAND2){
        return checkNandGate(gate);

    } 
    
    std :: cerr << "Incorrect gate encountered!\n";
    return false;
    
}

bool checkGateWrapper( GatePtr gate){

    if (!checkGate(gate)){
        std :: cerr << "Check failed for gate id: " << gate->getGateId() << "\n";
        return false;
    }

    if (gate->getGateType() == INPUT){
        return true;
    }

    
    bool res = checkGate(gate);

    if (!res) return false;

    for (auto &elem: gate->getInputGate()){
        res = res & checkGateWrapper(elem);

        if (!res){
            break;
        }
    }

    return res;

}

void traverseGate( GatePtr gate, GateStats* stats){
    if (gate->getGateType() == INPUT){
        (stats->inCount) += 1;
    } else if (gate->getGateType() == OUTPUT){
        (stats->outCount) += 1;
    } else if (gate->getGateType() == NOT){
        (stats->notCount) += 1;
    } else if (gate->getGateType() == NAND2){
        (stats->nandCount) += 1;
    }

    std :: cerr << "traverseGate:: Invalid gate found\n";

    for(GatePtr elem: gate->getInputGate()){
        traverseGate(elem, stats);
    }
}

GateStats* getStats(GatePtr gate){
    GateStats* stats = new GateStats();

    traverseGate(gate, stats);

    return stats;    
}
