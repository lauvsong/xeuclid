#include <stdio.h>
#include <openssl/bn.h>

BIGNUM *XEuclid(BIGNUM *x, BIGNUM *y, const BIGNUM *a, const BIGNUM *b)
{
        BIGNUM *r1 = a;
        BIGNUM *r2 = b;
        BIGNUM *x1 = 1;
        BIGNUM *x2 = 0;
        BIGNUM *y1 = 0;
        BIGNUM *y2 = 1;

        BIGNUM *r;
        BIGNUM *q;
        BIGNUM *rem;
        BN_CTX *ctx;
        BIGNUM *tmp;

        while(r2){
                q = 0;
                rem = 0;
                BN_div(q,rem,r1,r2,ctx);
                r1 = r2, r2=rem;

                BN_mul(tmp,q,x2,ctx);
                BN_sub(x,x1,tmp);
                x1 = x2, x2 = x;

                BN_mul(tmp,q,y2,ctx);
                BN_sub(y,y1,tmp);
                y1 = y2, y2 = y;
        }
        x = x1, y = y1;
        return r2;
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