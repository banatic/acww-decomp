/* func_ov003_02233e4c @ 0x02233e4c, 0xfc bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;
typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_02233e4c;

extern UnkStruct_02233e4c *data_020ccf94;
extern int func_02073dd4(UnkStruct_02233e4c *g, int a);
extern int func_020a7278(void);
extern void func_ov003_02233f48(unsigned char *self, Vec3 *v, int *d, unsigned char *b, int i, int flag);
extern void func_ov068_02271cec(unsigned char *self, unsigned char *b, Vec3 *out);

int func_ov003_02233e4c(unsigned char *self, Vec3 *out)
{
    int ret;
    int best;
    int flag;
    unsigned char i;
    unsigned int a254;
    int z;
    unsigned char b[2];
    int d;
    Vec3 v;
    unsigned int n;

    ret = 0;
    best = 0x0fffffff;
    flag = 1;
    b[0] = 1;
    b[1] = 1;
    a254 = self[0x254];
    n = self[0x255];
    out->x = 0;
    if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64)) {
        if (func_020a7278() == 0) {
            flag = 0;
        }
        i = 0;
        z = 0;
        do {
            func_ov003_02233f48(self, &v, &d, &b[1], i, flag);
            b[0] = (unsigned char) ((b[0] & b[1]) ? 1 : z);
            if (best > d) {
                out->x = v.x;
                out->y = v.y;
                out->z = v.z;
                best = d;
            }
            i = (unsigned char) (i + 1);
        } while (i < 4);
    } else {
        func_ov068_02271cec(self, b, out);
    }
    if (flag) {
        unsigned char *p = &self[0x254];
        unsigned int cur = *p;
        if (b[0] != 0 && cur != 0) {
            cur = (unsigned char) (cur - 1);
            *p = (unsigned char) cur;
        }
        if (n <= cur) {
            if (n > a254) {
                ret = 1;
            } else {
                ret = 3;
            }
        } else if (n > cur && n <= a254) {
            ret = 2;
        }
    }
    return ret;
}
