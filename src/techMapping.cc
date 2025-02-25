#include <iostream>
#include "TreeMatch/treeMatch.hh"

bool handleCommandLineArg (int argc, char * argv[]){
    assert(argc <= 2);
    bool debugMode = false;
    if (argc == 2){
        if (strcmp(argv[1], "-v") == 0){
            debugMode = true;
            std :: cout << "Debug mode is enabled\n";
        } else if (strcmp(argv[1], "-h") == 0){
            std :: cout << "Run this command to run without debug mode enabled: ./bin/techmap\n";
            std :: cout << "Run this command to run with debug mode enabled: ./bin/techmap -v\n";
            return 1;
        }
        else {
            std :: cout << "Argument not identified: "<< argv[1] << "Only vavlid argument: -v. Use ./bin/techmap -h for details \n"; 
            return 2;
        }
    }

    return debugMode;
}

int main(int argc, char* argv[]){    
    // Handling command line argument-------------------------
    bool debugMode = handleCommandLineArg(argc, argv);
    //--------------------------------------------------------
    TreeMatch techMap;

    if (debugMode) {
        techMap.setDebugMode();
    }
    
    techMap.run();
    techMap.print();
    
    return 0;

}

//TODO
/*
1) Currently netlist needs to be created by manually adding the function. Add a function which can take netlist in 
    text form and construct the netlist and also some basic checks.
2) Create Mapped netlist
*/