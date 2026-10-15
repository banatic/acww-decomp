/* func_02012214 @ 0x02012214, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02082c98(void *);
extern int func_02055d0c(void *, void *, int);
extern void func_0205e954(void *, void *);

void func_02012214(void *param0, void *param1)
{
    void *res;

    if (*(unsigned char *) ((char *) param0 + 0x3C) == 0) {
        return;
    }

    res = func_02082c98((char *) param0 + 4);

    if (param1 != 0) {
        func_02055d0c((char *) param1 + 0xEC, (char *) param0 + 0xC, 14);
    }

    if (res != 0) {
        func_0205e954(res, (char *) param0 + 0xC);
    }
}
