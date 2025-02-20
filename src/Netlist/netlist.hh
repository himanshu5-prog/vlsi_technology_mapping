#ifndef __NETLIST_HH__
#define __NETLIST_HH__

#include <iostream>
#include "../Gate/gate.hh"
#include "../CircuitCreator/circuitCreator.hh"

typedef Gate* GatePtr;
class Netlist {
  std :: vector <GatePtr> m_rootNetlist;
  int m_groupCount;
  int m_gateID;

  public:
    Netlist();
    ~Netlist();
    GatePtr createGate (GateType type);
    void createNetlist();
    void createNetlist_2();
    void print();
};

#endif