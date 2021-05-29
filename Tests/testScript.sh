#!/bin/bash
pgmName="minicc"
path="../src/"
#pour chaque fichier de test
failedTest=0
passedTest=0
totalTest=0
if [ ! -f pgmName ];then 
    if [ ! -f $path$pgmName ];then 
       cd $path && make;
    fi
    cp $path$pgmName ./$pgmName 
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
            ((totalTest=totalTest+1));
            $pgm $opt $f;
            if [ $? -eq 0 ];then
                ((passedTest=passedTest+1));
                echo "$f" passed
            else
                ((failedTest=failedTest+1));
                echo "$f" not passed
            fi
        done  
        
    elif [[ "$D" =~ KO ]];then
        for f in $D/*.tst; do
            ((totalTest=totalTest+1));
            $pgm $opt $f
            if [ $? -eq 0 ];then
                ((failedTest=failedTest+1));
                echo "$f" passed but should not                
            else
                ((passedTest=passedTest+1));
                echo "$f" failed as expected
            fi
        done   
    fi
done
echo -e "\t\t|\ttotal\t|\tfailed \t|\tpassed\t|"
echo -e "\t\t|\t"$((totalTest))"\t|\t"$((failedTest))"\t|\t"$((passedTest))"\t|"
