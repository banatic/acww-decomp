/* func_02072830 @ 0x02072830, 0xa8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020e98b4(unsigned int);
extern void func_020721ac(void *);
extern void func_02072180(void *, int);
extern void *func_0207282c(void *);
extern int func_02072da0(void *);
extern void func_0207216c(void *, int);
extern int func_02072260(void);
extern int func_02072d4c(void *);
extern void func_02072268(int, int, int);
extern int func_02072ee8(int);
extern int func_02095040(int);
extern void func_02064290(int, unsigned short);
extern void func_020950cc(int, unsigned short);
extern void func_020e9898(void *);

extern unsigned short data_020ccb64;
extern unsigned short data_020d185c;

int func_02072830(void *r5, unsigned int r6)
{
    void *r4;
    int a, b;

    if (r6 < 0x20) {
        r4 = func_020e98b4(0x200);
        if (r4 == 0) {
            goto ret1;
        }
        if (r4 != 0) {
            func_020721ac(r4);
        }

        func_02072180(r4, r6);

        a = func_02072da0(func_0207282c(r5));
        func_0207216c(r4, a);

        b = func_02072260();

        a = func_02072d4c(func_0207282c(r5));
        r6 += 0x12;
        func_02072268(b, a, r6);

        func_02064290(func_02095040(func_02072ee8(func_02072d4c(func_0207282c(r5)))), data_020ccb64);
        func_020950cc(func_02072ee8(func_02072d4c(func_0207282c(r5))), data_020d185c);

        func_020e9898(r4);
    ret1:
        return 1;
    }
    return 0;
}
