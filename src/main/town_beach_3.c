/* town_beach_3: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02047114 @ 0x02047114, 0x38 bytes, Thumb
 * func_020470c0 @ 0x020470c0, 0x54 bytes, Thumb
 */

#define NativeGridPredicate_func_02048e34 ((int (*)(int, int, int)) func_02048e34)

extern int func_020644cc(int);
extern int data_020cac9c[];
extern void func_0204a370(unsigned int, int, int, int);
extern int func_02048cb8(int, int, int, int, int, int (*predicate)(int, int, int), int);
extern int func_02048e34(int, int, int);
extern unsigned char data_021c7a08[];
extern unsigned char data_021c79c4[];

int func_02047114(void *object)
{
    unsigned short r4 = 0x1554;
    int r0 = func_020644cc(100);
    int *p = data_020cac9c;
    int i = 0;

    while (i < 9) {
        r0 -= *p;
        if (r0 < 0) {
            break;
        }
        r4 = (unsigned short) (r4 + 1);
        p++;
        i++;
    }
    return r4;
}

void func_020470c0(int a0, int a1, int a2)
{
    func_0204a370((unsigned int) data_021c79c4, a1, a2, 3);
    if ((int) ((unsigned char *) data_021c7a08 + a2 * 0x90)[0x88] < 4) {
        int x;
        x = func_02047114((void *) a0);
        func_02048cb8(a0, a1, a2 + 1, 4, x, NativeGridPredicate_func_02048e34, 0);
    }
}
