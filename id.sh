sed -i -e '$d' Data.gv
echo "label = \"Repo v." >> Data.gv
git log --pretty="format:%h" -1 >> Data.gv
echo "\"" >> Data.gv
echo "}" >> Data.gv
