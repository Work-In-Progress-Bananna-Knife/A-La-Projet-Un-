sed -i -e '$d' Data.gv
echo "label = \"#Commit nr." >> Data.gv
git log --pretty="format:%h" -1 >> Data.gv
echo "\"" >> Data.gv
echo "}" >> Data.gv
