/* func_0205971c @ 0x0205971c, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

extern unsigned char data_020e54a8;
typedef struct {
    int x, y, z;
} Vec3;
extern void func_ov003_022246c8(int, Vec3 *, Vec3 *, int, int, int);
extern void func_ov004_02233b5c(int, Vec3 *, Vec3 *, int, int, int);

static __inline int get_cond(void)
{
    return (data_020e54a8 == 0) ? 1 : 0;
}

void func_0205971c(int a0, int a1, Vec3 *a2, Vec3 *a3, short *a4)
{
    int cond;
    Vec3 v1, v2, v3, v4;

    cond = get_cond();

    if (cond == 1) {
        v1.x = a2->x;
        v1.y = a2->y;
        v1.z = a2->z;
        v2.x = a3->x;
        v2.y = a3->y;
        v2.z = a3->z;
        func_ov003_022246c8(a1, &v1, &v2, a4[0], a4[1], a4[2]);
    } else {
        v3.x = a2->x;
        v3.y = a2->y;
        v3.z = a2->z;
        v4.x = a3->x;
        v4.y = a3->y;
        v4.z = a3->z;
        func_ov004_02233b5c(a1, &v3, &v4, a4[0], a4[1], a4[2]);
    }
}
