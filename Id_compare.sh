sed -i -e '$d' Graph10.gv
echo "label = \"#Current Commit nr." >> Graph10.gv
git rev-parse --short HEAD >> Graph10.gv
echo "\"" >> Graph10.gv
echo "label = \"#Previous Commit nr." >> Graph10.gv
git rev-parse --short HEAD~1 >> Graph10.gv
echo "\"" >> Graph10.gv 
echo "}" >> Graph10.gv
