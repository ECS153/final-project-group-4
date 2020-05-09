# Project Proposal: One Time Pad

Our Group's Idea is to create a messaging application that is encrypted using the one time pad process. This Encryption technique is uncrackable on a cursory serach. The only disadvantage of this encryption technique is that two communicators must share a key, which is the one-time-pad, in a way that cannot be intercepted. This may mean that they meet in person to exchange a key, rely on a courier or a number or other techniques.

One time pad encryption relies on 4 pillars:
1. the key is truly random
2. The key is as long as the plaintext
3. The key never reused in part or in whole
4. The key is kept completly secret

We already have a couple resources to get started with:
* An encrypting/decrypting table: https://learningselfreliance.com/downloads/one-time-pad-cheat-sheet.pdf
* A example of a one time pad key: https://learningselfreliance.com/one_time_pad

The first steps to take:
* We need to implement the encryption/decription table into a program
* create a generator for the one time pads 
* create a application that allows users to send messages back and forth
