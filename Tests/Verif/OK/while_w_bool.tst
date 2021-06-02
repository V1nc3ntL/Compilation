
int start = 0;
int end = 100;
bool next = true;
int i = 1;
int sum = 0;
void main()
{
    sum = start;

    while(next){
        sum = sum + i;
        if(sum > end){
            next = false;
        }
    }
	print("sum: ",sum,"\n");
}

