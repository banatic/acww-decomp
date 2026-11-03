/* design_sets_2: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02072a48 @ 0x02072a48, 0x10 bytes, Thumb
 * func_02072a38 @ 0x02072a38, 0x10 bytes, Thumb
 * func_02072a28 @ 0x02072a28, 0x10 bytes, Thumb
 * func_02072998 @ 0x02072998, 0x90 bytes, Thumb
 * func_02072994 @ 0x02072994, 0x2 bytes, Thumb
 */

extern char *func_02072dbc(void *obj);
extern int func_02072da4(int arg);
extern int func_020e98b4(int);
extern void func_020e9898(int);
extern void func_020721dc(void);
extern void func_020721c4(int);
extern void *func_02072da0(void *record);
extern int func_020721b0(int, int);
extern int func_02072260(void);
extern void *func_02072d4c(void *record);
extern void *func_02072ee8(void *record);
extern void *func_02095040(void *record);
extern void func_020642d0(int, int);
extern int func_02072268(int, int, int);
extern void func_020950cc(int, unsigned short);
extern unsigned short data_020d1860;
extern unsigned char data_021dc7aa[];

void *func_02072994(void *record);

unsigned int func_02072a48(unsigned int r0, unsigned int r1)
{
    r1 &= 7;
    r1 *= 0x234;
    return r0 + r1;
}

void *func_02072a38(void *obj)
{
    func_02072dbc(obj);
    return obj;
}

int func_02072a28(int arg)
{
    func_02072da4(arg);
    return arg;
}

void func_02072998(int param)
{
    int result;
    int r6;
    result = func_020e98b4(0x200);
    if (result == 0) {
        return;
    }
    if (result != 0) {
        func_020721dc();
    }
    func_020721c4(result);
    func_020721b0(result, (int) func_02072da0(func_02072994((void *) param)));
    r6 = func_02072260();
    func_02072268(r6, (int) func_02072d4c(func_02072994((void *) param)), 0x10);
    func_020642d0((int) func_02095040(func_02072ee8(func_02072d4c(func_02072994((void *) param)))),
                  (unsigned int) data_021dc7aa);
    func_020950cc((int) func_02072ee8(func_02072d4c(func_02072994((void *) param))), data_020d1860);
    func_020e9898(result);
}

void *func_02072994(void *record)
{
    return record;
}
