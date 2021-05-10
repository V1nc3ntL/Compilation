#!/bin/bash
CompiledPgm="../src/minicc"
nbTestsPassed=0
nbTests=0
#pour chaque fichier de test
for D in `find .  -mindepth 1 -type d  `;do
    echo "Tests du dossier" $D
    #Enleve les dossiers intermédiaires
    if [ ! -d $D/OK ] 
    then
        for f in $D/*.tst; do
            value+=$(cat "$f")
            "$CompiledPgm" "$value"
            if [ $? -eq 0 ]
            then
                echo "$f" passed
                nbTestsPassed+=1
            else
                echo "$f" not passed
            fi
            nbTests+=1
        done
    fi
done
