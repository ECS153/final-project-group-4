-----Install-----

In this folder, is generating the main function for the project.

The whole process is based on the one-time_pad.cpp file.

In order to use the program, you need to do:

make

g++ one-time_pad.cpp

./a.out

-----Use the function-----

Then it will ask for one time pad elements for the table, if you just hit enter, it will use the standard table with elements
like the following:

!"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~

and then you need to enter the one time pad key and message, note: one time pad key needs to have at least message's length
and use the elements that is in the one time pad table (depends on the elements you input), other wise will cause an reinput action

