/* func_020470c0 @ 0x020470c0, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0204a370(unsigned int, int, int, int);
extern int func_02047114(void);
extern int func_02048cb8(int, int, int, int, int, int (*predicate)(int, int, int), int);
extern int func_02048e34(int, int, int);
#define NativeGridPredicate_func_02048e34 ((int (*)(int, int, int)) func_02048e34)

extern unsigned char data_021c7a08[];

extern unsigned char data_021c79c4[];

void func_020470c0(int a0, int a1, int a2)
{
    func_0204a370((unsigned int) data_021c79c4, a1, a2, 3);
    if ((int) ((unsigned char *) data_021c7a08 + a2 * 0x90)[0x88] < 4) {
        int x;
        asm { add r0, a0, #0 }
        x = func_02047114();
        func_02048cb8(a0, a1, a2 + 1, 4, x, NativeGridPredicate_func_02048e34, 0);
    }
}
