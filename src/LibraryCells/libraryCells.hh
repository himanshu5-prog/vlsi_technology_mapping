#ifndef __LIB_CELL_HH__
#define __LIB_CELL_HH__

#include <iostream>
#include <vector>
#include "../Gate/gate.hh"
#include "../CircuitCreator/circuitCreator.hh"

#define NOT_GATE_COST 2
#define NAND_GATE_COST 3
#define AND_GATE_COST 4
#define NOR_GATE_COST 6
#define OR_GATE_COST 4
#define AOI21_GATE_COST 7
#define AOI22_GATE_COST 7

typedef Gate* GatePtr;

struct TechCell {
    GatePtr root;
    GateType name;
    int cost;
};


class LibraryCells {
    int m_cellCount;
    std :: vector <TechCell> m_techCellVect; 
    public:

    LibraryCells();
    void init();
    ~LibraryCells();

    GatePtr createNotGate();
    GatePtr createNandGate();
    GatePtr createAndGate();
    GatePtr createNorGate();
    GatePtr createOrGate();
    GatePtr createAOI21();
    GatePtr createAOI21_rotated();
    GatePtr createAOI22();

    void print();
    std :: vector <TechCell> getTechCell();

};
#endif