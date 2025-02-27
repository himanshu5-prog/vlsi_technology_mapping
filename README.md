# Technology Mapping using minimum cost tree-covering

This repository implements technology mapping algorithm using minimum cost tree-covering.

Technology mapping takes synthesized netlist and convert into another netlist which uses technology library cells. These cells have actual area, dimension and delay while the input synthesized netlist is just connection of gates.

The input netlist and library cells are assumed to be a tree and contain just Not and Nand2 cells. Each technology cell is mapped to every node in input netlist and technology cells are used so that the cost is minimum. The cost can be area or delay or maybe some combination of these two metrics.

## Compiling the code:

Use this command:

> source run.tcl # For compilation

> ./bin/techmap -v  # To run the code with debug mode enabled

OR

> ./bin/techmap  #To run with debug mode disabled

## Brief explanation of source code:

1) src/Gate/gate.* : Gate class is described which has function to process a gate like adding gate on inuput side.

2) src/LibraryCells/libraryCells.* : All library cells are constructed.

    List of Library cells:
    i) NOT
   
    ii) NAND2
   
    iii) OR2
   
    iv) AND2
   
    v) NOR2
   
    vi) AOI21 ( And-or-Invert)
   
    vii) AOI22 (And-or-Invert containing 2 input for each of 2 nand2 cells )

    There is another cell AOI21_rotated which is same as AOI21 but it is just in rotated form. This cell is constructed for the tech mapping using technology mapping.

    ![Technology Library Cells](docs/images/tech_libcells_1.png)

    ![Technology Library Cells](docs/images/tech_libcells_2.png)
4) src/Netlist/netlist.* : This class constructs input netlist. Currently netlist is constructed by adding function and use it for every circuit.

    ![Sample Netlist](docs/images/sample_netlist.png)
    Above is sample netlist which is made of NOT and NAND2 gates
6) src/CircuitCreator/circuitCreator.*: These files contain helper function used to create netlist.

7) src/TreeMatch/treeMatch.* : This class contains function for recursive tree matching and minimum cost tree covering.

## Log file:

1) run.log: Log file of output generated for a sample netlist showing the possible mapping and best mapping which provide minimum cost.

-> The output is the valid mapping for every node in netlist. We will also get best mapping and the minimum cost that we get using that mapping.

TODO: Need to generate final mapped netlist. Will push the change once it is done.

## Understanding the netlist in log file:


---------------------------------------------------------------------------------------------------------------------------
current gate id: 101, gate type: NOT

input gate count: 1

Input gates:

Gate id: 102, gate type: NAND2

---------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------
current gate id: 102, gate type: NAND2

input gate count: 2

Input gates:

Gate id: 103, gate type: INPUT

Gate id: 104, gate type: INPUT

Here we have two logic gates and two input pad. The netlist is printed using map data structure. Each element shows the input gate information.

The first element shows NOT gate and has NAND2 (id: 102) connected. If we go to the next element in hash, we will come to NAND2 (id: 102). This gate is connected to two input pad.


## Understanding the output:

Mapped Netlist gate count: 1

---------------------------------------------------

Gate id: 101, type: AND2

Mapped gate: 

Gate id: 103, type: INPUT

Gate id: 104, type: INPUT

**********************************************

Here, the logical gate discussed before can be mapped to technology mapped AND2 cell which is functionally equivalent to the logical netlist.

## Reference:

I took this Coursera course: VLSI: Logic to Layout and learnt about technology mapping. I really liked the course and wanted to implement something which uses knowledge of data structure and algorithm. The minimum cost tree covering is great application of tree data structure, dynamic programming and recursive algorithm.

Link to course:
https://www.coursera.org/learn/vlsi-cad-layout 
