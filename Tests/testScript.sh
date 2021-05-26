#!/bin/bash
CompiledPgmName="../src/minicc"
#pour chaque fichier de test

if [ ! -f "minicc" ];then 

    cp $CompiledPgmName .

fi

pgm="./minicc"

for D in `find .  -mindepth 2 -type d  `;do

    if [[ "$D" =~ Verif ]];then
        #opt="-v"
        opt=""
    elif [[ "$D" =~ Syntaxe ]];then
        opt="-s"
    else
        opt=""
    fi

    if [[ "$D" =~ OK ]];then
        for f in $D/*.tst; do        
            $pgm $opt $f
            if [ $? -eq 0 ];then
                echo "$f" passed
            else
                echo "$f" not passed
            fi
        done  
        
    elif [[ "$D" =~ KO ]];then
        for f in $D/*.tst; do
            $pgm $opt $f
            if [ $? -eq 0 ];then
                echo "$f" passed but should not                
            else
                echo "$f" failed as expected
            fi
        done   
    fi
done
