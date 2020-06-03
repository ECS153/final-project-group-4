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

and then you need to choose which mode you want to use, either "encryption" or "decryption" for "a" and "b" as input.

Next, you need to enter the one time pad key and message, note: one time pad key needs to have at least message's length
and use the elements that is in the one time pad table (depends on the elements you input), otherwise will cause an reinput action.

After you input all things (table elements, mode, one time pad key, message), you will get the result after encryption or
decryption, and some files will be create:

1. tableelement.txt: this is about the elements we use in the table

2. inputOneTimePadkey.txt: this is the one time pad key you input

3. InputMessage.txt: this is the message you input

4. outputQRcode.html: when you open this html, it will appear a QR code, if you scan it, you will have the output after encryption or decryption, and you are able to let others to scan and copy it.

