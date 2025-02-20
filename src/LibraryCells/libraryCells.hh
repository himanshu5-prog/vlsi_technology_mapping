#ifndef __LIB_CELL_HH__
#define __LIB_CELL_HH__

#include <iostream>
#include <vector>
#include "../Gate/gate.hh"
#include "../CircuitCreator/circuitCreator.hh"

#define NOT_GATE_COST 2
#define NAND_GATE_COST 3
#define AND_GATE_COST 4
#define NOR_GATE_COST 5
#define OR_GATE_COST 6
#define AOI21_GATE_COST 4
#define AOI22_GATE_COST 5;

typedef Gate* GatePtr;

struct TechCell {
    GatePtr root;
    GateType name;
    int cost;
};


class LibraryCells {
    int cellCount;
    std :: vector <TechCell> techCell;
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
    GatePtr createAOI22();

    void print();

};
#endif