/* func_02050a84 @ 0x02050a84, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02050a84 {
    unsigned int size;
    int result;
};

extern void CARDi_RequestStreamCommand(int b, int a, int c, int d, int e, int f, int g, int h, int i);
extern void func_0211ec44(unsigned short value);
extern int OS_GetLockID(unsigned int size, int sum, int b, int c);
extern int func_02050974(struct UnkStruct_02050a84 *p);
extern void func_02050948(struct UnkStruct_02050a84 *p);

int func_02050a84(struct UnkStruct_02050a84 *p, int a, int b, int c)
{
    int ret = 1;

    if ((unsigned) (a + c) > p->size) {
        return ret;
    }

    p->result = OS_GetLockID(p->size, a + c, b, c);

    if (p->result == -3) {
        return ret;
    }

    func_0211ec44((unsigned short) p->result);
    CARDi_RequestStreamCommand(b, a, c, 0, 0, 1, 7, 10, 2);

    if (func_02050974(p) == 3) {
        ret = 3;
    } else {
        func_02050948(p);
    }

    return ret;
}
