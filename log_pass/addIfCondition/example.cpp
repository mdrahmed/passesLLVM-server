#include <stdio.h>

int add(int a,int b){
	return a+b;
}


int main(int argc, const char** argv) {
    int a,b;
    scanf("%d %d", &a,&b);
    printf("add func: %d",add(a,b));
    if(a> 10){
        printf("%d\n",a + 2);
    }
    else{
            printf("Num is less than 10");
    }
    return 0;
}

