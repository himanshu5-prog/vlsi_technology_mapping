#include "netlist.hh"

Netlist::Netlist(){
    m_groupCount = 0;
    m_gateID = 0;
}

GatePtr
Netlist :: getRootNetlist(){
    return m_rootNetlist;
}

void
Netlist :: createNetlist_2(){
    // Unique gate id for each gate
    int gateId = 0;    

    // Create output pad. Each netlist will have only 1 output pad
    GatePtr outputPad = createPrimitivePad(gateId, OUTPUT);
    ++gateId;

    // The netlist contains 5 Not gate
    std :: vector<GatePtr> notGate (5);

    // Netlist contains 11 Nand2 gates
    std :: vector<GatePtr> nandGate (11);

    // Netlist contains 12 input pads
    // Input pad only has gate connected to its output. 
    std :: vector<GatePtr> inputPad(12);

    // Creating Not gates
    for (int i = 0; i < notGate.size(); ++i){
        notGate[i] = createPrimitiveNotGate(gateId);
        ++gateId;
    }

    // Creating Nand2 gates. Nand2 has 2 inputs.
    for (int i = 0; i < nandGate.size(); ++i){
        nandGate[i] = createPrimitiveNandGate(gateId);
        ++gateId;
    }

    // Creating Input pads
    for (int i = 0; i < inputPad.size(); ++i){
        inputPad[i] = createPrimitivePad(gateId, INPUT);
        ++gateId;
    }

    // Connecting not gate to input of output pad
    outputPad->addInputGate(notGate[0]);

    // Input of Not  gate is connected to nand gate
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
    
    // Output pad is the root to the tree. Adding the root to class member variable
    m_rootNetlist = (outputPad);
}

void
Netlist::print(){
   m_rootNetlist->printGate();
}

Netlist:: ~Netlist(){
    delete m_rootNetlist;
}