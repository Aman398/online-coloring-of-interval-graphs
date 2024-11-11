# Recoloring Interval Graphs with Limited Recourse Budget - Algorithm Implementations
## Overview
This repository contains implementations of the algorithms described in the research paper "Recoloring Interval Graphs with Limited Recourse Budget" by Bartłomiej Bosek, Yann Disser, Andreas Emil Feldmann, Jakub Pawlewicz, and Anna Zych-Pawlewicz.
The paper explores dynamic graph coloring algorithms under the constraint of a limited recourse budget, specifically for interval graphs.

I have attempted to implement the algorithms presented in the paper, including both the upper and lower bounds for the required recourse budget in dynamic interval graph recoloring. In addition, I’ve included a few test cases to verify the correctness of my implementation, specifically focusing on testing the KT algorithm and other dynamic recoloring methods discussed in the paper.

## Algorithms Implemented
- **KT Algorithm**: A dynamic coloring algorithm with limited recourse.
- **Recourse Budget Bounds**: Upper and lower bound calculations for interval graphs.
- **Unit Interval Graph** Coloring: Efficient recoloring with restricted budgets.
- **Additional Algorithms**: Algorithms for implicit and amortized time complexity handling as described in the paper.
## Features
- **Dynamic Updates**: Support for interval insertion with recoloring.
## Research Paper
The algorithms and methods implemented in this repository are based on the paper titled *Recoloring Interval Graphs with Limited Recourse Budget* by Bartłomiej Bosek et al. The paper studies the recoloring of dynamically arriving interval graphs while minimizing the number of recolorings, which is bound by a parameter called the recourse budget.

For more details, you can refer to the original paper:
[*Recoloring Interval Graphs with Limited Recourse Budget* (SWAT 2020)](https://doi.org/10.4230/LIPIcs.SWAT.2020.17).
