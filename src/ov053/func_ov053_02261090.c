/* func_ov053_02261090 @ 0x02261090, 0x60 bytes, Thumb, module ov053
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a, b, c;
} Vec3;

extern Vec3 data_ov053_02261814;
extern unsigned short data_020c80f8;
extern int func_0200322c(void *dst, Vec3 *src);
extern int func_02019d0c(void *p, int a, int b, int c, int d, int e, int f, int g, int h, int i, int j);

int func_ov053_02261090(char *p)
{
    Vec3 local;
    int ret;

    *(unsigned char *) (p + 0x719) = 0;
    local.a = data_ov053_02261814.a;
    local.b = data_ov053_02261814.b;
    local.c = data_ov053_02261814.c;
    ret = func_0200322c(p + 0x5c, &local);
    func_02019d0c(p + 0x564, 3, 1, 0, 0, 0, ret, 0, 0, (int) data_020c80f8, 0);
    return 1;
}
