#!/bin/bash
CompiledPgm="../src/minicc"
#pour chaque fichier de test
for D in `find .  -mindepth 2 -type d  `;do
    tmpPgm=$CompiledPgm
    if [[ "$D" =~ Verif ]];then
    tmpPgm+=" -v"
    elif [[ "$D" =~ Syntaxe ]];then
    tmpPgm+=" -s"
    fi
    echo $tmpPgm
    if [[ "$D" =~ OK ]];then
        for f in $D/*.tst; do
            value=$(cat "$f")
            echo tested program : $tmpPgm 
            if[ [ "$D" =~ OK ]]
            "$tmpPgm" $f
            if [ $? -eq 0 ]
            then
                echo "$f" passed
            else
                echo "$f" not passed
            fi
        done  
    elif [[ "$D" =~ KO ]];then
        for f in $D/*.tst; do
            value=$(cat "$f")
            echo tested  : $tmpPgm $value
            "$tmpPgm" $f
            if [ $? -eq 0 ];then
                echo "$f" passed but should not                
            else
                echo "$f" failed as expected
            fi
        done   
    fi
done
