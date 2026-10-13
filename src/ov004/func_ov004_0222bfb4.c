/* func_ov004_0222bfb4 @ 0x0222bfb4, 0x58 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0222bfb4 {
    int x, y, z;
};

extern void *func_02096718(int a);
extern int func_ov004_0222683c(void *p, struct UnkStruct_0222bfb4 *v, int k, int m);
extern int func_ov004_02227e94(void *p, int k, int m);

int func_ov004_0222bfb4(void)
{
    char *p = (char *) func_02096718(4);

    if (p != 0) {
        if (*(int *) (p + 0x808) == 4) {
            struct UnkStruct_0222bfb4 v;
            struct UnkStruct_0222bfb4 *q = (struct UnkStruct_0222bfb4 *) (p + 0x5c);
            v.x = *(int *) (p + 0x5c);
            v.y = q->y;
            v.z = q->z;
            v.z = v.z + 0x6000;
            return func_ov004_0222683c(p, &v, 6, -1);
        }
        return func_ov004_02227e94(p, 6, -1);
    }
    return 0;
}
