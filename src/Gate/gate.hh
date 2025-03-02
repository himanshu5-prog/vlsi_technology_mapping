#ifndef __GATE_HH__
#define __GATE_HH__
#include <iostream>
#include <vector>
#include <memory>


enum GateType {
    INPUT,
    OUTPUT,
    NOT,
    AND2,
    NAND2,
    OR2,
    NOR2,
    AOI21,
    AOI21_ROTATED,
    AOI22,
    NA

};

std :: string getStringGateType (GateType g);

struct GateStats {
    int outCount;
    int inCount;
    int notCount;
    int nandCount;

    GateStats(){
        outCount = 0;
        inCount = 0;
        notCount = 0;
        nandCount = 0;
    }
};

/*
Each gate will have 1 output and multiple inputs.
*/
       
class Gate {
  typedef Gate* GatePtr;

    GateType m_gateType;
    int m_gateId;
    bool m_mapped;

    int m_inputCount;
    std :: vector <GatePtr> m_inputGate;
    std :: vector <int> m_inputGateId;

    public:

        //Constructor and destructor
        Gate();
        Gate(GateType g, int id, int ipCount, std :: vector<GatePtr> inGate);
        ~Gate();

        // Get methods-----------------------

        // Gate type
        GateType getGateType() const;

        // Gate ID
        int getGateId() const;

        // Input side 
        int getInputCount() const;
        std :: vector <GatePtr> getInputGate();
        bool isMapped();
        //-------------------------------------    
        // Set methods--------------------------------
        void setGateType(GateType g);
        void setGateId (int id);

        void setInputCount(int c);
        void setInputGate( std :: vector < GatePtr > v);
        void setMapped();
        //--------------------------------------------
        void addInputGate(GatePtr g){
            m_inputGate.push_back(g);
            m_inputGateId.push_back(g->getGateId());
        }

        void printGate() const;
};

#endif