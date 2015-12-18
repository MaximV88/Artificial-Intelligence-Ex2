# Artificial-Intelligence-Ex2
This repository contains my solution for implementing value iterator (and resulting policy display) in a way that allows for easy customization. There is a reward and score calculation models which can be extended for further functionality.

The input must be in a .txt file named "input.txt". The output will be written to a new file named "output.txt".

The built in costs are:
* Road = 1
* Dirt = 3
* Hill = 10

The end tile (G) has a reward of 100.

After performing the Algorithm the output will be formatted by row, 
with each X value being iterated before incrementing the Y value (i.e. going to the next row).

###Example

Contents of "input.txt":

4<br />
SHWW<br />
RRWD<br />
RRWD<br />
WRRG<br />

Contents of "output.txt":

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