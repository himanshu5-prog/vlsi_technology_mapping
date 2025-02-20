#include "netlist.hh"

Netlist::Netlist(){
    m_groupCount = 0;
    m_gateID = 0;
}

void
Netlist :: createNetlist_2(){
    int gateId = 0;    
    GatePtr outputPad = createPrimitivePad(gateId, OUTPUT);
    ++gateId;

    std :: vector<GatePtr> notGate (5);
    std :: vector<GatePtr> nandGate (11);
    std :: vector<GatePtr> inputPad(12);

    for (int i = 0; i < notGate.size(); ++i){
        notGate[i] = createPrimitiveNotGate(gateId);
        ++gateId;
    }

    for (int i = 0; i < nandGate.size(); ++i){
        nandGate[i] = createPrimitiveNandGate(gateId);
        ++gateId;
    }

    for (int i = 0; i < inputPad.size(); ++i){
        inputPad[i] = createPrimitivePad(gateId, INPUT);
        ++gateId;
    }

    outputPad->addInputGate(notGate[0]);
    notGate[0]->addInputGate(nandGate[0]);

    nandGate[0]->addInputGate(nandGate[1]);
    nandGate[0]->addInputGate(nandGate[2]);

    nandGate[1]->addInputGate(nandGate[3]);
    nandGate[1]->addInputGate(nandGate[4]);

    nandGate[2]->addInputGate(nandGate[5]);
    nandGate[2]->addInputGate(nandGate[6]);

    nandGate[3]->addInputGate(nandGate[7]);
    nandGate[3]->addInputGate(notGate[1]);

    nandGate[4]->addInputGate(notGate[2]);
    nandGate[4]->addInputGate(notGate[3]);

    nandGate[5]->addInputGate(nandGate[8]);
    nandGate[5]->addInputGate(notGate[4]);

    nandGate[6]->addInputGate(nandGate[9]);
    nandGate[6]->addInputGate(nandGate[10]);

    notGate[1]->addInputGate(inputPad[0]);

    nandGate[7]->addInputGate(inputPad[1]);
    nandGate[7]->addInputGate(inputPad[2]);

    notGate[2]->addInputGate(inputPad[3]);
    notGate[3]->addInputGate(inputPad[4]);

    nandGate[8]->addInputGate(inputPad[5]);
    nandGate[8]->addInputGate(inputPad[6]);

    notGate[4]->addInputGate(inputPad[7]);

    nandGate[9]->addInputGate(inputPad[8]);
    nandGate[9]->addInputGate(inputPad[9]);

    nandGate[10]->addInputGate(inputPad[10]);
    nandGate[10]->addInputGate(inputPad[11]);
    
    m_rootNetlist.push_back(outputPad);
}

void
Netlist::print(){
    for (const GatePtr elem: m_rootNetlist){
        elem->printGate();
    }
}

Netlist:: ~Netlist(){
    for (auto elem: m_rootNetlist){
        delete elem;
    }
}