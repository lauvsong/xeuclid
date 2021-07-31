#include <stdio.h>
#include <openssl/bn.h>

BIGNUM *XEuclid(BIGNUM *x, BIGNUM *y, const BIGNUM *a, const BIGNUM *b)
{
        BIGNUM *r1 = BN_new();
        BIGNUM *r2 = BN_new();
        BIGNUM *s1 = BN_new();
        BIGNUM *s2 = BN_new();
        BIGNUM *t1 = BN_new();
        BIGNUM *t2 = BN_new();

        BIGNUM *q = BN_new();
        BIGNUM *r = BN_new();
        BN_CTX *ctx = BN_CTX_new();
        BIGNUM *tmp = BN_new();

        BN_copy(r1, a);
        BN_copy(r2, b);
        BN_one(s1);
        BN_zero(s2);
        BN_zero(t1);
        BN_one(t2);

        while(!BN_is_zero(r2)){
                BN_div(q,r,r1,r2,ctx);
                BN_copy(r1, r2);
                BN_copy(r2, r);

                BN_mul(tmp,q,s2,ctx);
                BN_sub(x,s1,tmp);
                BN_copy(s1, s2);
                BN_copy(s2, x);

                BN_mul(tmp,q,t2,ctx);
                BN_sub(y,t1,tmp);
                BN_copy(t1, t2);
                BN_copy(t2, y);
        }
        BN_copy(x, s1);
        BN_copy(y, t1);
        return r1;
}

void printBN(char *msg, BIGNUM * a)
{
        char *num = BN_bn2dec(a);
        printf("%s %s\n", msg, num);
        OPENSSL_free(num);
}


int main (int argc, char *argv[])
{
        BIGNUM *a = BN_new();
        BIGNUM *b = BN_new();
        BIGNUM *x = BN_new();
        BIGNUM *y = BN_new();
        BIGNUM *gcd;

        if(argc != 3){
                printf("usage: xeuclid num1 num2");
                return -1;
        }
        BN_dec2bn(&a, argv[1]);
        BN_dec2bn(&b, argv[2]);
        gcd = XEuclid(x,y,a,b);

	printBN("(a,b) = ", gcd);
        printBN("a = ", a);
        printBN("b = ", b);
        printBN("x = ", x);
        printBN("y = ", y);
        printf("%s*(%s) + %s*(%s) = %s\n",BN_bn2dec(a),BN_bn2dec(x),BN_bn2dec(b),BN_bn2dec(y),BN_bn2dec(gcd));

        if(a != NULL) BN_free(a);
        if(b != NULL) BN_free(b);
        if(x != NULL) BN_free(x);
        if(y != NULL) BN_free(y);
        if(gcd != NULL) BN_free(gcd);

        return 0;
}