#ifndef __NETLIST_HH__
#define __NETLIST_HH__

#include <iostream>
#include "../Gate/gate.hh"
#include "../CircuitCreator/circuitCreator.hh"

typedef Gate* GatePtr;
class Netlist {
  GatePtr m_rootNetlist;
  int m_groupCount;
  int m_gateID;

  public:
    Netlist();
    ~Netlist();
    void createNetlist_2();
    void createSimpleCircuit();
    void createLogicAOI21Rotated();
    void print();
    GatePtr getRootNetlist();
};

#endif