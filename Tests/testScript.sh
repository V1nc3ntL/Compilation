#!/bin/bash
pgmName="minicc"
path="../src/"
marsPath="../tools/Mars_4_2.jar nc np"
marsCmd="java -jar"
fst=""
tstExtension=".tst"
rstExtension=".rst"
#pour chaque fichier de test
failedTest=0
passedTest=0
totalTest=0
tstFailed=""
if [ ! -f pgmName ];then 
    if [ ! -f $path$pgmName ];then 
       cd $path && make;
    fi
    cp $path$pgmName ./$pgmName 
fi

pgm="./minicc"

for D in `find .  -mindepth 2 -type d  `;do

    if [[ "$D" =~ Verif ]];then
        opt="-v"
        fst=""
    elif [[ "$D" =~ Syntaxe ]];then
        fst=""
        opt="-s"
    else
        fst=marsCmd
        opt=
    fi

    
    if [[ "$D" =~ Gencode ]];then
        if [[ "$D" =~ OK ]];then
            for f in $D/*$tstExtension; do  
                ((totalTest=totalTest+1));      
                $pgm $opt $f ;
                echo $marsCmd $marsPath;
                $marsCmd $marsPath $opt out.s > results;
                cat results
                cmp --silent results  "${f/$tstExtension/$rstExtension}";

                 if [ $? -eq 0 ];then
                    ((passedTest=passedTest+1));
                    echo "$f" passed
                else
                    ((failedTest=failedTest+1));
                    tstFailed+="\t${f}\n"
                    echo "$f" not passed
                fi
                rm results;
            done
        else 
            for f in $D/*$tstExtension; do        
                ((totalTest=totalTest+1));
                $pgm $opt $f ;
                $marsCmd $marsPath out.s ;
            done
        fi
    else
        if [[ "$D" =~ OK ]];then
            for f in $D/*$tstExtension; do        
                ((totalTest=totalTest+1));
                $pgm $opt $f;
                if [ $? -eq 0 ];then
                    ((passedTest=passedTest+1));
                    echo "$f" passed
                else
                    tstFailed+="\t${f}\n"
                    ((failedTest=failedTest+1));
                    echo "$f" not passed
                fi
            done  
            
        elif [[ "$D" =~ KO ]];then
            for f in $D/*$tstExtension; do
                ((totalTest=totalTest+1));
                $pgm $opt $f
                if [ $? -eq 0 ];then
                    tstFailed+="\t${f}\n"
                    ((failedTest=failedTest+1));
                    echo "$f" passed but should not                
                else
                    ((passedTest=passedTest+1));
                    echo "$f" failed as expected
                fi
            done   
        fi
    fi
done
echo -e "\t\t|\ttotal\t|\tfailed \t|\tpassed\t|"
echo -e "\t\t|\t"$((totalTest))"\t|\t"$((failedTest))"\t|\t"$((passedTest))"\t|"
echo -e "\n Failed tests are :"
echo -e $tstFailed
