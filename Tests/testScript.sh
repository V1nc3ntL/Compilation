#!/bin/bash
CompiledPgm="../src/minicc"
#pour chaque fichier de test
for D in `find .  -mindepth 2 -type d  `;do
    if [[ "$D" =~ OK ]];then
        for f in $D/*.tst; do
            value+=$(cat "$f")
            echo tested command : $CompiledPgm $value
            "$CompiledPgm" "$value"
            if [ $? -eq 0 ]
            then
                echo "$f" passed
            else
                echo "$f" not passed
            fi
        done   
    elif [[ "$D" =~ KO ]];then
        for f in $D/*.tst; do
            value+=$(cat "$f")
            echo tested command : $CompiledPgm $value
            "$CompiledPgm" "$value"
            if [ $? -eq 0 ];then
                echo "$f" passed but should not                
            else
                echo "$f" failed as expected
            fi
        done   
    fi
done
