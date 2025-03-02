#include "libraryCells.hh"

LibraryCells :: LibraryCells (){
    m_cellCount = 0;
}

LibraryCells :: ~LibraryCells(){
}

GatePtr
LibraryCells :: createNotGate(){

    /*
        OUT
         | 
        NOT
         |
        IN
    */
    GatePtr outputPad = createPrimitivePad (0,OUTPUT);
    GatePtr notGate = createPrimitiveNotGate(1);

    outputPad->addInputGate(notGate);

    GatePtr inputPad = createPrimitivePad(2,INPUT);

    notGate->addInputGate(inputPad);

    return outputPad;
}

GatePtr
LibraryCells :: createNandGate (){
    /*
        OUT
         |
        NAND
       /    \
      IN     IN
    
    */
    GatePtr outputPad = createPrimitivePad (0, OUTPUT);
    GatePtr nandGate = createPrimitiveNandGate(1);

    outputPad->addInputGate(nandGate);
    GatePtr inputPad_0 = createPrimitivePad(2,INPUT);

    GatePtr inputPad_1 = createPrimitivePad(3, INPUT);

    nandGate->addInputGate(inputPad_0);
    nandGate->addInputGate(inputPad_1);

    return outputPad;
}

GatePtr
LibraryCells :: createAndGate(){
    /*
        OUT
         |
        NOT
         |
        NAND 
       /    \
      IN     IN
    */
    GatePtr outputPad = createPrimitivePad (0, OUTPUT);
    GatePtr notGate = createPrimitiveNotGate(1);

    outputPad->addInputGate(notGate);
    GatePtr nandGate = createPrimitiveNandGate (2);

    notGate->addInputGate(nandGate);
    GatePtr inputPad_0 = createPrimitivePad (3, INPUT);

    GatePtr inputPad_1 = createPrimitivePad(4, INPUT);

    nandGate->addInputGate(inputPad_0);
    nandGate->addInputGate(inputPad_1);

    return outputPad;
}

GatePtr
LibraryCells :: createNorGate (){

    /*
            OUT
             |
            NOT
             |
            NAND
           /    \
          NOT    NOT
           |      |
           IN     IN
    
    */
    GatePtr outputPad = createPrimitivePad (0, OUTPUT);
    GatePtr notGate_0 = createPrimitiveNotGate(1);

    outputPad->addInputGate(notGate_0);
    GatePtr nandGate = createPrimitiveNandGate(2);

    notGate_0->addInputGate(nandGate);
    GatePtr notGate_1 = createPrimitiveNotGate(3);

    nandGate->addInputGate(notGate_1);
    GatePtr notGate_2 = createPrimitiveNotGate(4);

    nandGate->addInputGate(notGate_2);
    GatePtr inputPad_0 = createPrimitivePad (5, INPUT);
    GatePtr inputPad_1 = createPrimitivePad(6, INPUT);

    notGate_1->addInputGate(inputPad_0);
    notGate_2->addInputGate(inputPad_1);

    return outputPad;
}

GatePtr
LibraryCells :: createOrGate() {
    /*
           OUT
            |
           NAND
         /    \
        NOT    NOT
         |      |
        IN     IN
    */
    GatePtr outputPad = createPrimitivePad (0, OUTPUT);
    GatePtr nandGate = createPrimitiveNandGate(1);

    outputPad->addInputGate(nandGate);
    GatePtr notGate_1 = createPrimitiveNotGate(2);
    GatePtr notGate_2 = createPrimitiveNotGate(3);

    nandGate->addInputGate(notGate_1);
    nandGate->addInputGate(notGate_2);

    GatePtr inputPad_0 = createPrimitivePad (4, INPUT);
    GatePtr inputPad_1 = createPrimitivePad(5, INPUT);

    notGate_1->addInputGate(inputPad_0);
    notGate_2->addInputGate(inputPad_1);


    return outputPad;
}

GatePtr
LibraryCells :: createAOI21() {
    /*
        OUTPUT
            |
           NOT
            |
           NAND
          /    \
        NAND    NOT
        /  \     |
      IN   IN    IN
    */
    GatePtr outputPad = createPrimitivePad (0, OUTPUT);
    GatePtr notGate_1 = createPrimitiveNotGate(1);

    outputPad->addInputGate(notGate_1);

    GatePtr nandGate_1 = createPrimitiveNandGate(2);
    
    notGate_1->addInputGate(nandGate_1);

    GatePtr nandGate_2 = createPrimitiveNandGate(3);
    GatePtr notGate_2 = createPrimitiveNotGate(4);

    nandGate_1->addInputGate(nandGate_2);
    nandGate_1->addInputGate(notGate_2);

    GatePtr inputPad_1 = createPrimitivePad(5, INPUT);
    GatePtr inputPad_2 = createPrimitivePad(6, INPUT);

    nandGate_2->addInputGate(inputPad_1);
    nandGate_2->addInputGate(inputPad_2);

    GatePtr inputPad_3 = createPrimitivePad(7, INPUT);

    notGate_2->addInputGate(inputPad_3);

    return outputPad;
}


GatePtr
LibraryCells :: createAOI21_rotated() {
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
    GatePtr outputPad = createPrimitivePad (0, OUTPUT);
    GatePtr notGate_1 = createPrimitiveNotGate(1);

    outputPad->addInputGate(notGate_1);

    GatePtr nandGate_1 = createPrimitiveNandGate(2);
    
    notGate_1->addInputGate(nandGate_1);

    GatePtr nandGate_2 = createPrimitiveNandGate(3);
    GatePtr notGate_2 = createPrimitiveNotGate(4);

    // Just need to re-arrange how nandGate_2 and notgate_2 are connected
    // to nandGate_1
    //nandGate_1->addInputGate(nandGate_2);
    //nandGate_1->addInputGate(notGate_2);

    nandGate_1->addInputGate(notGate_2);
    nandGate_1->addInputGate(nandGate_2);
    
    GatePtr inputPad_1 = createPrimitivePad(5, INPUT);
    GatePtr inputPad_2 = createPrimitivePad(6, INPUT);

    nandGate_2->addInputGate(inputPad_1);
    nandGate_2->addInputGate(inputPad_2);

    GatePtr inputPad_3 = createPrimitivePad(7, INPUT);

    notGate_2->addInputGate(inputPad_3);

    return outputPad;
}

GatePtr
LibraryCells :: createAOI22() {

    /*
        OUTPUT
            |
           NOT
            |
           NAND
          /    \
        NAND    NAND
        /  \     /  \
      IN   IN   IN   IN
    */
    GatePtr outputPad = createPrimitivePad (0, OUTPUT);
    GatePtr notGate_1 = createPrimitiveNotGate(1);

    outputPad->addInputGate(notGate_1);

    GatePtr nandGate_1 = createPrimitiveNandGate(2);
    
    notGate_1->addInputGate(nandGate_1);

    GatePtr nandGate_2 = createPrimitiveNandGate(3);
    GatePtr nandGate_3 = createPrimitiveNandGate(4);

    nandGate_1->addInputGate(nandGate_2);
    nandGate_1->addInputGate(nandGate_3);

    std :: vector <GatePtr> inputPad(4,nullptr);

    for(unsigned long i = 0; i < inputPad.size(); ++i){
        inputPad[i] = createPrimitivePad(i+5, INPUT);
    }

    nandGate_2->addInputGate(inputPad[0]);
    nandGate_2->addInputGate(inputPad[1]);

    nandGate_3->addInputGate(inputPad[2]);
    nandGate_3->addInputGate(inputPad[3]);

    return outputPad;

}

void 
LibraryCells :: init() {
    
   TechCell t;

   t.root = createNotGate();
   t.cost = NOT_GATE_COST;
   t.name = NOT;
   m_techCellVect.push_back(t);

   t.root = createNandGate();
   t.cost = NAND_GATE_COST;
   t.name = NAND2;
   m_techCellVect.push_back(t);

   t.root = createAndGate();
   t.cost= AND_GATE_COST;
   t.name = AND2;
   m_techCellVect.push_back(t);

   t.root = createNorGate();
   t.cost = NOR_GATE_COST;
   t.name = NOR2;
   m_techCellVect.push_back(t);

   t.root = createOrGate();
   t.cost = OR_GATE_COST;
   t.name = OR2;
   m_techCellVect.push_back(t);

   t.root = createAOI21();
   t.cost = AOI21_GATE_COST;
   t.name = AOI21;
   m_techCellVect.push_back(t);

   t.root = createAOI22();
   t.cost = AOI22_GATE_COST;
   t.name = AOI22;
   m_techCellVect.push_back(t);

   t.root = createAOI21_rotated();
   t.cost = AOI21_GATE_COST;
   t.name = AOI21_ROTATED;
   m_techCellVect.push_back(t);

   m_cellCount = m_techCellVect.size();

}

void
LibraryCells :: print() const {
    std :: cout << "Total tech cell: " << m_cellCount << "\n";
    for (auto &elem: m_techCellVect){
        std :: cout << "Name: " << getStringGateType(elem.name) << "\n";
        std :: cout << "Printing the gate:\n";
        elem.root->printGate();
        std :: cout << "------------------------------------------------------\n";
    }
    
}

std :: vector <TechCell>
LibraryCells :: getTechCell() const{
    return m_techCellVect;
}