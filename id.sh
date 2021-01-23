sed -i -e '$d' Data.gv
echo "label = \"#Commit nr." >> Data.gv
git rev-parse --short HEAD >> Data.gv
echo "\"" >> Data.gv
echo "}" >> Data.gv


