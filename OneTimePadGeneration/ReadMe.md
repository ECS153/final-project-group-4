-----Install-----

In this folder, is generating the main function for the project.

The whole process is based on the one-time_pad.cpp file.

In order to use the program, you need to do:

make

pip3 install MyQR

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

4. outputQRcode.html: when you open this html, it will appear a QR code, if you scan it, you will have the output after encryption or decryption, and you are able to let others to scan and copy it. This one can use for the one time pad table that is contain special character, but not the qrcode.png file

5. outputMessage.txt: this is the message after encrpytion / decryption

6. qrcode.png: this is the qr code for the outputmessage, here use myqr, but the qr code that comes out will be right when your one time pad table did not contain special character, which is:

7. pop up window: it will first try to use google chrome to open the html version qr code, but if you do not have a google chome, it will open the png version qr code for you

ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890

-----source code-----
I posted the source that I use in this one time pad in my one-time_pad.cpp file, such as:

https://github.com/nayuki/QR-Code-generator

https://github.com/sylnsfar/qrcode/blob/master/README-cn.md

https://blog.csdn.net/xiangxianghehe/article/details/77351721

https://en.cppreference.com/w/cpp/utility/program/system
