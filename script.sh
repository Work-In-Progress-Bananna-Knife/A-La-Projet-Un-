#/bin/bash
circo -Tpng Data.gv -o graf.png
circo -Tplain Data.gv -o paradigm.txt
display graf.png
open graf.png