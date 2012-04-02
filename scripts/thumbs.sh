#!/bin/bash
for i in files/*.jpg
do
echo "Processing $i ..."
/usr/bin/convert -thumbnail 100 "$i" thumbnails/thumb.$(basename "$i")
done

for i in files/*.JPG
do
echo "Processing $i ..."
/usr/bin/convert -thumbnail 100 "$i" thumbnails/thumb.$(basename "$i")
done


