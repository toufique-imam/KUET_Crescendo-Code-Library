
string t,p;
int b[N];
void kmpPreprocess() {
    int m=p.size();
    int i=0,j=-1;
    b[0]=-1;
    while(i<m) {
        while(j>-1 && p[i]!=p[j])
            j=b[j];
        i++;
        j++;
        b[i]=j;
    }
}
void printFailure(){
    int len=p.size();
    for(int i=0;i<=len;i++){
        printf("%d ",b[i]);
    }
    printf("\n");
}
void kmpSearch() {
    int i=0,j=0;
    int m=p.size();
    int n=t.size();
    while(i<n) {
        while(j>-1 && t[i]!=p[j])
            j=b[j];
        i++;
        j++;
        if(j==m) {
            printf("P is found at index %d in T\n",i-j);
            j=b[j];
        }
    }
}
