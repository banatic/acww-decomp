/* func_02028b74 @ 0x02028b74, 0x8e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0207f270(int);
extern int func_020794d0(int);
extern int func_0209bd44(void *);
extern int func_020984e8(void);
extern int func_02099020(int, int);
extern int func_020644cc(int);
extern int func_0209bd04(int);
extern int func_0209bc88(int);
extern int func_02028d04(int, int, int);
extern int func_02028f5c(int, int, int);
extern int func_02028c04(int, int, int);

int func_02028b74(int a, int b, int c)
{
    int v;
    int result;

    v = func_020794d0(func_0207f270(b));
    result = 0;

    if (func_0209bd44((void *) v) == 0) {
        goto end;
    }
    if (func_02099020(func_020984e8(), 1) != 0) {
        goto end;
    }
    if (func_020644cc(100) >= 30) {
        goto end;
    }

    switch (func_0209bd04(v)) {
        case 0:
            result = func_02028d04(a, b, c);
            break;
        case 1:
            switch (func_0209bc88(v)) {
                case 0:
                    break;
                case 1:
                    result = func_02028f5c(a, b, c);
                    break;
                case 3:
                    result = func_02028c04(a, b, c);
                    break;
            }
            break;
    }

end:
    return result;
}
