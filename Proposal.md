# Project Proposal: One Time Pad

Our Group's Idea is to create a messaging application that is encrypted using the one-time pad process. This Encryption technique is uncrackable on a cursory search. The only disadvantage of this encryption technique is that two communicators must share a key, which is the one-time-pad, in a way that cannot be intercepted. This may mean that they meet in person to exchange a key, rely on a courier or a number or other techniques. There is one other problem that makes this encryption less effective than in the days of WW2 is that communications can still be tracked via metadata, I believe we can solve this with some trickery using a dead drop onto a web app that we will build.

One time pad encryption relies on 4 pillars:
1. the key is truly random
2. The key is as long as the plaintext
3. The key never reused in part or in whole
4. The key is kept completely secret

There are a few caveats with our implementation that may be resolved if there is an abundance of time:
* I think generating truly random numbers is outside the scope of this project and using a standard pseudo-random number generator will be fine
* We will just assume that the two end-users will be able to share the key somehow

We already have a couple of resources to get started with:
* An encrypting/decrypting table: https://learningselfreliance.com/downloads/one-time-pad-cheat-sheet.pdf
* An example of a one-time pad key: https://learningselfreliance.com/one_time_pad

The first steps to take:
* We need to implement the encryption/decryption table into a program
* create a generator for the one-time pads 
* create an application that allows users to send messages back and forth

Webapp:
In order to implement the dead drop we create a web server that anyone can upload text onto, hopefully, this is ciphertext. the ciphertext is preceded by a keyword that the communicators agree on, probably when they share the keys. This way communicators can find their partners easily, but if the entire user base works on one webpage metadata is not enough to tie them to any one person they are communicating with. This is possible without compromising the security of the messages because of the properties of OTP encryption. The ciphertext is essentially blasted out to everyone but it only has meaning to people who have the key.
