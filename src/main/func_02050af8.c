/* func_02050af8 @ 0x02050af8, 0x7e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int OS_GetLockID(void);
extern void func_0211ec44(unsigned short v);
extern int CARDi_RequestStreamCommand(int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8, int p9);
extern void func_0211ec34(unsigned short v);
extern void OS_ReleaseLockID(unsigned short v);

struct UnkStruct_02050af8 {
    unsigned int size;
    int value;
};

int func_02050af8(struct UnkStruct_02050af8 *p, int a, int b, int c)
{
    int result = 1;

    if ((unsigned) (a + c) > p->size) {
        return result;
    }

    p->value = OS_GetLockID();
    if (p->value == -3) {
        return result;
    }

    func_0211ec44((unsigned short) p->value);

    if (CARDi_RequestStreamCommand(b, a, c, 0, 0, 0, 7, 10, 2)) {
        result = 0;
    }

    func_0211ec34((unsigned short) p->value);
    OS_ReleaseLockID((unsigned short) p->value);

    p->value = -3;
    return result;
}
