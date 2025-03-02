#ifndef __NETLIST_HH__
#define __NETLIST_HH__

#include <iostream>
#include "../Gate/gate.hh"
#include "../CircuitCreator/circuitCreator.hh"

typedef Gate* GatePtr;
class Netlist {
  GatePtr m_rootNetlist;

  public:
    //Constructor and destructor
    Netlist();
    ~Netlist();
    //--------------------------------
    // Methods to create netlist
    // These are four available netlists which can be used. Note, only netlist can be used.
    // Additional netlist can be created by adding the method in this class
    void createNetlist_2();
    void createSimpleCircuit();
    void createLogicAOI21Rotated();
    void createSimpleNor();

    //Print method
    void print() const;

    // Get method
    GatePtr getRootNetlist() const;
};

#endif