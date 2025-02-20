#ifndef __CIRCUIT_CREATOR_HH__
#define __CIRCUIT_CREATOR_HH__

#include <iostream>
#include <cassert>
#include <map>
#include "../Gate/gate.hh"

typedef Gate* GatePtr;
typedef std :: map <GatePtr, std :: vector <GatePtr>> GateHashMap;

GatePtr createPrimitiveNotGate(int id);
GatePtr createPrimitiveNandGate(int id);
GatePtr createPrimitivePad(int id, GateType type);

GateHashMap createHashMap(GatePtr gate);
void traverseGateHash(GatePtr gate);
void printGateHash (GateHashMap h);
bool checkNotGate(GatePtr gate);
bool checkNandGate(GatePtr gate);
bool checkOutputPad(GatePtr gate);
bool checkInputPad(GatePtr gate);
bool checkGate(GatePtr gate);
bool checkGateWrapper(GatePtr gate);
GateStats* getStats(Gate gate);

#endif