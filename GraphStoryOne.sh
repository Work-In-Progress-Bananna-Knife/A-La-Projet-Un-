#/bin/bash
dot -Tpng Data.gv -o GraphStoryOne.png
dot -Tpng functions.txt -o GraphStoryTwo.png
display GraphStoryOne.png
