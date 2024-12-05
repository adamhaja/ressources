#!/bin/sh

export PREFIX_DIR=./
export README_FILE=README.html

echo "Content-Type: text/html\n\n"

READ=$(echo $QUERY_STRING | grep -oE "(^|[?&])read=[^&]+" | cut -d= -f2)
if [ -z $READ ]; then READ=$README_FILE ; fi
FILEPATH=$PREFIX_DIR$READ

if [ ! -r $FILEPATH ]; then
    echo "<span style='color:red;'>erreur! (<tt>$FILEPATH</tt>)</span>" ;
else
if [ $FILEPATH = $PREFIX_DIR$README_FILE ]; then
    cat $FILEPATH ;
else
    echo "<textarea style='width:95%; height:95%;' readonly='readonly'>";
    cat $FILEPATH ;
    echo "</textarea>";
fi fi

