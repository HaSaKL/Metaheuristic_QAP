This implements a Tabu Search Metaheuristic for the Quadratic Assignment Problme (QAP) using the ParadisEO Metaheuristic Framework.

The implementation is based on an example implementation from   The Van LUONG (The-Van.Luong@inria.fr) and Mahmoud FATENE, (mahmoud.fatene@inria.fr) from the DOLPHIN Project-Team, INRIA Lille Nord Europe. It can be downloaded at http://gforge.inria.fr/frs/download.php/file/22473/QAP.zip.
Unfortunately, this example does not work with ParadiseEO v2.0. To demonstrate an learn the MO-part of ParadisEO I re-implemented all Classes necessary to at least carry out a Tabu Search (TS) for a given QAP Problem. In the original example the QAP is solved by TS, by a genetic algorithm and by a hybrid algorithm, using TS and the  genetic algorithm. Further, it contains a sequentiual and a parallel implementation. Here, you only find a sequential implementation of the TS.

Some things could be done better, using the infrastructure from the framework. E.g. it could directly use a eoInt-Representation or the eoInitPermutation-classes. However, the purpose of this project was to get to know what needs to be implemented to get a running algorithm, aiming at the GQAP and the Service Modularization Problem. For those problems, custom representations need to be developed and the implicit self-made implementation allows - IMHO - a better understanding and example on how to do so.

To build the project you need to have ParadisEO-2.0.1 installed (can be obtained from http://paradiseo.gforge.inria.fr/)
After getting the source, you can do the following in the project folder to build the example

mkdir build
cd build
cmake ..
make

An example Problem from Quadratic Assignment Problem Library (http://anjos.mgi.polymtl.ca/qaplib/) can be found in the folder ($project_folder)/application (NOT! in build/application!)

To call applications do from project folder

cd build/applications
./QAP_test -p="../../application/chr12a.dat"

or

cd build/applications
./QAP_TS -p="../../application/chr12a.dat"
