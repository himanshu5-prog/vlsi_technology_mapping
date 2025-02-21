--------------- Technology Mapping----------------------------------

This repository implements technology mapping algorithm using minimum cost tree-covering. 

Technology mapping takes synthesized netlist and convert into another netlist which uses technology library cells. These cells have actual area, dimension and delay. The input synthesized netlist is just connection of gates.

The input netlist is assumed to be a tree along with cells in technology library. Each technology cell is mapped to every node in input netlist and technology cells are used so that the cost is minimum. The cost can be area or delay among other things.