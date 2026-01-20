#include <stdio.h>
#include <locale.h>
int main(){
    setlocale(LC_ALL, "");
    int a, b, c, d, e;
    scanf("%d %d %d %d %d", &a, &b, &c, &d, &e);
    printf("сумма:%d разность:%d произведение:%d остаток1:%d остаток2:%d остаток3:%d остаток4:%d остаток5:%d размер1:%d размер2:%d размер3:%d размер4:%d размер5:%d", a+b+c+d+e, a-b-c-d-e, a*b*c*d*e, a%10, b%10, c%10, d%10, e%10, sizeof(a), sizeof(b), sizeof(c), sizeof(d), sizeof(e));
    return 0;
}
