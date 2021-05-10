#!/bin/bash
CompiledPgm="../src/minicc"
#pour chaque fichier de test
for D in `find . -type d -mindepth 1`;do
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
            else
                echo "$f" not passed

            fi
        done
    fi
done
