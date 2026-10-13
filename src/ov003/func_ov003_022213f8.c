/* func_ov003_022213f8 @ 0x022213f8, 0x6a bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_022213f8 {
    int x, y;
};
struct UnkStruct_022213f8_2 {
    int x, y, z;
};

extern void *func_0204e414(void);
extern int func_ov003_02221464(int a, int b);
extern void func_ov003_02222880(int a, int b, struct UnkStruct_022213f8 *l1, struct UnkStruct_022213f8_2 *l2, int e,
                                unsigned short f, void *p, short g, int h);

int func_ov003_022213f8(int a, int b, struct UnkStruct_022213f8 *c, struct UnkStruct_022213f8_2 *d, int e, unsigned short f,
                        short g, int h)
{
    void *alloc;
    int flag;
    int result;
    struct UnkStruct_022213f8 l1;
    struct UnkStruct_022213f8_2 l2;

    alloc = func_0204e414();
    if (alloc == 0) {
        return 0;
    }

    flag = 0;
    result = func_ov003_02221464(a, b);
    if (result != 0) {
        l2.x = d->x;
        l2.y = d->y;
        l2.z = d->z;
        l1.x = c->x;
        l1.y = c->y;
        func_ov003_02222880(result, b, &l1, &l2, e, f, alloc, g, h);
        flag = 1;
    }
    return flag;
}
