
# GOAP C++ implementation

This folder contains an implementation of the GOAP algorithm described in "Three States and a plan: The AI of F.E.A.R" by Orkin (2006).
The idea of GOAP is to extend the finite state machines typically used for game agents.
In this model, instead of explicitely modelling transitions between states, constrains are expressed and a state machine is generated from those.
Only transitions that respect the constrains are expressed, and then a path to the desired end-state can be found.


```
mkdir build && cd build
cmake ..
make example
./example
```
