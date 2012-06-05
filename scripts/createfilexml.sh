#!/bin/bash
files="testimeta.txt"
outfile="file.xml"
utf8file="meta.xml"
#rootdir="Qt/jkl-dvd/jkl-dvd-build-desktop/Demoon/"
export rootdir="/home/tuutai/gitrepo/qtfd-build/tiedostot/store/"
export targetdir="../../qtfd-build/files/"

mkdir -p $targetdir

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

cat $outfile | sed s/\:/\./g > korjattu_$outfile
mv korjattu_$outfile $outfile

cat $outfile |iconv --from-code=ISO-8859-1 > $utf8file
