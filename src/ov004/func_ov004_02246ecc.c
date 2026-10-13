/* func_ov004_02246ecc @ 0x02246ecc, 0x28 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;
extern char *data_021c67a4;
extern int func_0203c0ac(char *p, int a);
int func_ov004_02246ecc(Vec3 *src)
{
    Vec3 *d = (Vec3 *) (data_021c67a4 + 0x1cc);
    d->x = src->x;
    d->y = src->y;
    d->z = src->z;
    return func_0203c0ac(data_021c67a4, 0x14);
}
