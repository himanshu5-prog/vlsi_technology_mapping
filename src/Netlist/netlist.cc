#include "netlist.hh"

Netlist::Netlist(){
    m_rootNetlist = nullptr;
}

GatePtr
Netlist :: getRootNetlist() const{
    return m_rootNetlist;
}

void
Netlist :: createSimpleCircuit(){
    /*
          OUTPUT
            |
           NOT
            |
           NAND
          /    \
        IN      IN
    */
    // Create output pad. Each netlist will have only 1 output pad
    GatePtr outputPad = createPrimitivePad(100, OUTPUT);
    
    // Create Not gate
    GatePtr notGate = createPrimitiveNotGate(101);

    // Create Nand gate
    GatePtr nandGate = createPrimitiveNandGate(102);
    outputPad->addInputGate(notGate);

    notGate->addInputGate(nandGate);

    GatePtr inputPad_0 = createPrimitivePad(103,INPUT);
    GatePtr inputPad_1 = createPrimitivePad(104, INPUT);

    nandGate->addInputGate(inputPad_0);
    nandGate->addInputGate(inputPad_1);
    m_rootNetlist = (outputPad);
}

void
Netlist :: createLogicAOI21Rotated(){
    /*
            OUTPUT
                |
               NOT
                |
               NAND
              /    \
            NOT    NAND
             |      /  \
            IN     IN  IN    
    */
    GatePtr outputPad = createPrimitivePad(100, OUTPUT);
    GatePtr notGate = createPrimitiveNotGate(101);
    GatePtr nandGate = createPrimitiveNandGate(102);

    outputPad->addInputGate(notGate);
    notGate->addInputGate(nandGate);

    GatePtr notGate_1 = createPrimitiveNotGate(103);
    GatePtr nandGate_1 = createPrimitiveNandGate(104);

    nandGate->addInputGate(notGate_1);
    nandGate->addInputGate(nandGate_1);

    GatePtr inputpad_1 = createPrimitivePad(105, INPUT);
    GatePtr inputpad_2 = createPrimitivePad(106, INPUT);
    GatePtr inputpad_3 = createPrimitivePad(107, INPUT);

    notGate_1->addInputGate(inputpad_1);

    nandGate_1->addInputGate(inputpad_2);
    nandGate_1->addInputGate(inputpad_3);

    m_rootNetlist = outputPad;

    
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
    for (unsigned int i = 0; i < notGate.size(); ++i){
        notGate[i] = createPrimitiveNotGate(gateId);
        ++gateId;
    }

    // Creating Nand2 gates. Nand2 has 2 inputs.
    for (unsigned int i = 0; i < nandGate.size(); ++i){
        nandGate[i] = createPrimitiveNandGate(gateId);
        ++gateId;
    }

    // Creating Input pads
    for (unsigned int i = 0; i < inputPad.size(); ++i){
        inputPad[i] = createPrimitivePad(gateId, INPUT);
        ++gateId;
    }

    // Connecting not gate to input of output pad
    outputPad->addInputGate(notGate[0]);

    // Input of Not  gate is connected to nand gate
    notGate[0]->addInputGate(nandGate[0]);

    nandGate[0]->addInputGate(nandGate[1]); // gate: 6 getting inpconnected
    nandGate[0]->addInputGate(nandGate[2]);

    GatePtr notGate_2 = createPrimitiveNotGate(400);
    
   // nandGate[1]->addInputGate(nandGate[3]); 
   nandGate[1]->addInputGate(notGate_2);
    notGate_2->addInputGate(nandGate[3]);
    nandGate[1]->addInputGate(nandGate[4]);

    //nandGate[2]->addInputGate(nandGate[5]);
    
    nandGate[2]->addInputGate(nandGate[6]);

    nandGate[3]->addInputGate(nandGate[7]);
    nandGate[3]->addInputGate(notGate[1]);

    nandGate[4]->addInputGate(notGate[2]);
    nandGate[4]->addInputGate(notGate[3]);

    GatePtr notGate_3 = createPrimitiveNotGate(500);
    nandGate[2]->addInputGate(notGate_3);
    nandGate[5]->addInputGate(notGate[4]);
    nandGate[5]->addInputGate(nandGate[8]);

    notGate_3->addInputGate(nandGate[5]);


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

void Netlist :: createSimpleNor(){
    /*
        OUTPUT
          |
         NOT
          |
         NAND
        /    \
      NOT    NOT
       |      |
      IN      IN
    */
    GatePtr outputPad = createPrimitivePad(120, OUTPUT);
    GatePtr notGate = createPrimitiveNotGate(121);

    GatePtr nandGate = createPrimitiveNandGate(122);
    GatePtr notGate_1 = createPrimitiveNotGate(123);
    GatePtr notGate_2 = createPrimitiveNotGate(124);

    outputPad->addInputGate(notGate);
    notGate->addInputGate(nandGate);

    nandGate->addInputGate(notGate_1);
    nandGate->addInputGate(notGate_2);

    GatePtr inputPad_1 = createPrimitivePad(125, INPUT);
    GatePtr inputPad_2 = createPrimitivePad(126, INPUT);

    notGate_1->addInputGate(inputPad_1);
    notGate_2->addInputGate(inputPad_2);

    m_rootNetlist = outputPad;
}

void
Netlist::print() const{
    std:: cout << "****************************\n";
    std::cout << "Printing Netlist:\n";
    m_rootNetlist->printGate();
    std :: cout << "****************************\n";
}

Netlist:: ~Netlist(){
    //delete m_rootNetlist;
}