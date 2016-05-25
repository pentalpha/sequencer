Highly parallelized algorithm (using OpenMP) for sequencing segments of text in order to return the full text.

Input - lines of text (%% = \n):

"Casa aba %% data

data live stream"



Output - full text:

"Casa aba

data live stream"

Algorithm made for the Bioinformatics Hackathon (http://bioinformatica.imd.ufrn.br/snnb/), won first place with a run time of 0.05s.

----------------------------------------

Tarefa para o Hackaton 2016 (Seminario Bioinformatica)

----------------------------------------

How to build and run:

Building the app: $ make all

The executable will be "sequencer"

For help about the command line arguments: $ ./sequencer --help

Building the tests: $ make testes

The tests are "testSegmentSet" and "testStringMerge"

If the executables dont have execution rights: $ chmod 755 <file_name>