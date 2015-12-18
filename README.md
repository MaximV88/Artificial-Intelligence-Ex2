# Artificial-Intelligence-Ex2
This repository contains my solution for implementing value iterator (and resulting policy display) in a way that allows for easy customization. There is a reward and score calculation models which can be extended for further functionality.

###Example

For an input that is formatted as:

4<br />
SHWW<br />
RRWD<br />
RRWD<br />
WRRG<br />

in a .txt file named "input.txt", the resulting output will be:

0,0,D<br />
0,1,D<br />
1,0,RD<br />
1,1,D<br />
1,3,D<br />
2,0,R<br />
2,1,D<br />
2,3,D<br />
3,1,R<br />
3,2,R<br />