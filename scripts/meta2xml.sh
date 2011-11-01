#!/bin/bash
filename=$1

if [ ! -f $filename ]
then
echo "Tiedostoa ei löydy: $filename" 1>&2
exit 1
fi

tmpfile="/tmp/meta.tmp"
/bin/cp $filename $tmpfile
/bin/sed -i \r $tmpfile
/bin/sed -i 's/'"$(printf '\015')"'//g' $tmpfile
/bin/sed -i 's/ *$//' $tmpfile

nimi=`/bin/grep Tiedostonimi $tmpfile| /bin/sed 's/.*: *//' | /bin/sed 's/ /_/g'`
pvm=`/bin/grep pvm $tmpfile| /bin/sed 's/.*: *//' | /bin/sed 's/\t/ /'| /bin/sed 's/ *$//'  | /bin/sed 's/,/./g'`
if [ ! -n "$pvm" ]
then
echo "Varoitus: Tyhjä pvm: $filename" 1>&2
exit 1
#echo `/bin/grep pvm $tmpfile` 1>&2
fi
kat=`/bin/grep Kategoria $tmpfile| /bin/sed 's/.*: *//' | /usr/bin/awk -F, '{print $1}'`
alakat=`/bin/grep Alakategoria $tmpfile| /bin/sed 's/.*: *//' | /bin/sed 's/ /_/g' | /bin/sed 's/,/ /g'`
otsikko=`/bin/grep Otsikko $tmpfile| /bin/sed 's/.*: *//'`
kuvaus=`/bin/grep Kuvaus $tmpfile| /bin/sed 's/.*: *//'`
kirjoittaja=`/bin/grep Kirjoittaja $tmpfile| /bin/sed 's/.*: *//'`
kirjoituspvm=`/bin/grep Kirjoitusp $tmpfile | /usr/bin/awk -F: '{print $2}'`
hakusanat=`/bin/grep Hakusanat $tmpfile| /bin/sed 's/.*: *//' | /bin/sed 's/ /_/g' | /bin/sed 's/,/ /g'`

/bin/rm $tmpfile

echo "         <file>"
n=`echo $nimi | /bin/sed 's/_/ /g'`
echo "                <name>$n</name>"
echo "                <date>$pvm</date>"
echo "                <categories>"
echo "                 <category>"
echo "                  <catname>$kat</catname>"
echo "                  <subcategories>"
for ak in $alakat
do
a=`echo $ak | /bin/sed 's/_/ /g'`
a=`echo $a | /bin/sed 's/^ *//'`
echo "                   <scatname>$a</scatname>"
done
echo "                  </subcategories>"
echo "                 </category>"
echo "                </categories>"
echo "                <topic>$otsikko</topic>"
echo "                <description>$kuvaus</description>"
echo "                <writer>$kirjoittaja</writer>"
echo "                <writedate>$kirjoituspvm</writedate>"
echo "                <searchtags>"
for sana in $hakusanat
do
s=`echo $sana | /bin/sed 's/_/ /g'`
s=`echo $s | /bin/sed 's/^ *//'`
echo "                 <stag>$s</stag>"
done
echo "                </searchtags>"
echo "         </file>"

