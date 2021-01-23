git show HEAD Data.gv | tee Graph10.gv

#usuwanie wszystkiego do wystąpienia danego wyrażenia razem z nim
sed -i -e '1,/@@/d' Graph10.gv

#usuwanie ostatniej linii
sed -i -e '$d' Graph10.gv

#usuwanie znaku
sed -i -e 's/;//' Graph10.gv

#zmiana koloru odjętych
sed -i -e '/^-/ s/$/&[color = red]/' Graph10.gv

#zmiana koloru dodanych
sed -i -e '/^+/ s/$/&[color = green]/' Graph10.gv

#usuwanie pierwszego znaku z każdej linii
sed -i -e 's/^.//' Graph10.gv

#usuwanie danego znaku z pliku
#sed -i -e 's/+//' Graph10.gv

#usuwanie danego znaku z pliku
#sed -i -e 's/-//' Graph10.gv

##usuwanie lini z danym znakiem
#sed -i -e '/^-/d' Graph10.gv

sed -i -e 's/}//' Graph10.gv
echo "}" >> Graph10.gv


