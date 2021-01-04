#/bin/bash
dot -Tpng Data.gv -o graf.png
circo -Tplain-ext Data.gv -o paradigm.txt
display graf.png
open graf.png