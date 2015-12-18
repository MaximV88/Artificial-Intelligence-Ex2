# Artificial-Intelligence-Ex2
This repository contains my solution for implementing value iterator (and resulting policy display) in a way that allows for easy customization. There is a reward and score calculation models which can be extended for further functionality.

###Example

For an input that is formatted as:

4
SHWW\n
RRWD\n
RRWD\n
WRRG\n

in a .txt file named "input.txt", the resulting output will be:

0,0,D\n
0,1,D\n
1,0,RD\n
1,1,D\n
1,3,D\n
2,0,R\n
2,1,D\n
2,3,D\n
3,1,R\n
3,2,R\n