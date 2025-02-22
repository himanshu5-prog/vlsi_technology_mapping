------------------------------------Technology Mapping----------------------------------

This repository implements technology mapping algorithm using minimum cost tree-covering.

Technology mapping takes synthesized netlist and convert into another netlist which uses technology library cells. These cells have actual area, dimension and delay while the input synthesized netlist is just connection of gates.

The input netlist and library cells are assumed to be a tree and contain just Not and Nand2 cells. Each technology cell is mapped to every node in input netlist and technology cells are used so that the cost is minimum. The cost can be area or delay or maybe some combination of these two metrics.

Here is the brief explanation of source code:

1) src/Gate/gate.* : Gate class is described which has function to process a gate like adding gate on inuput side.

2) src/LibraryCells/libraryCells.* : All library cells are constructed.

    List of Library cells:
    i) NOT
    ii) NAND2
    iii) OR2
    iv) AND2
    v) NOR2
    v) AOI21 ( And-or-Invert)
    vi) AOI22 (And-or-Invert)

    There is another cell AOI21_rotated which is same as AOI21 but it is just in rotated form. This cell is constructed for the tech mapping using technology mapping.

3) src/Netlist/netlist.* : This class constructs input netlist. Currently netlist is constructed by adding function and use it for every circuit.

4) src/CircuitCreator/circuitCreator.*: These files contain helper function used to create netlist.

5) src/TreeMatch/treeMatch.* : This class contains function for recursive tree matching and minimum cost tree covering.
