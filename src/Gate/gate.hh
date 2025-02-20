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
    typedef std::shared_ptr<Gate> SharedGatePtr;
    typedef std::weak_ptr<Gate> WeakGatePtr;

    typedef Gate* GatePtr;


    GateType gateType;
    int gateId;
    bool m_mapped;
    
    // Output side
    //GatePtr outputGate;
    //int outputGateId;

    int inputCount;
    std :: vector <GatePtr> inputGate;
    std :: vector <int> inputGateId;

    public:
        Gate();
        Gate(GateType g, int id, GatePtr gPtr, int ipCount, std :: vector<GatePtr> inGate);
        ~Gate();
        // Get methods

        // Gate type
        GateType getGateType();

        // Gate ID
        int getGateId();

        // Fanout gate pointer
        //GatePtr getOutputGate();
        //int getOutputGateId(){
        //    return outputGateId;
        //}

        // Input side 
        int getInputCount();
        std :: vector <GatePtr> getInputGate();
        std :: vector <int> getinputGateId;

        // Set methods
        void setGateType(GateType g);
        void setGateId (int id);

        void setInputCount(int c);
        void setInputGate( std :: vector < GatePtr > v);
        void addInputGate(GatePtr g){
            inputGate.push_back(g);
            inputGateId.push_back(g->getGateId());
        }
        void addInputGateId(int i){
            inputGateId.push_back(i);
        }

        //void setOutputGate (GatePtr g);
        //void setOutputGateId(int i){
        //     outputGateId = i;
        //}


        void printGate();


};
#endif