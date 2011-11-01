#!/bin/bash
files="testimeta.txt"
outfile="file.xml"
utf8file="meta.xml"
#rootdir="Qt/jkl-dvd/jkl-dvd-build-desktop/Demoon/"
rootdir="/home/tuutai/gitrepo/qtfd-build/Tallessa20111031yhdistetty"

echo "<xml>" > $outfile
echo "        <files>" >> $outfile
/usr/bin/find $rootdir -name '*.txt' | while read f
do
#f=`/bin/echo $f |sed 's/ /\\ /g'`
n=`echo $f | /usr/bin/awk '{print NF}'`
if [ "$n" -gt 1 ]
then
echo "Virheellinen tiedostonimi: $f"
echo " : välilyönti ei ole sallittu"
else
./meta2xml.sh $f >> $outfile
fi
done
echo "        </files>" >> $outfile
echo "</xml>" >> $outfile

cat $outfile |iconv --from-code=ISO-8859-1 > $utf8file
