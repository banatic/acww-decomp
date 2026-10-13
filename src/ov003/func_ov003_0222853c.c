/* func_ov003_0222853c @ 0x0222853c, 0xdc bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;

extern char data_ov003_0225f76c[];
extern char data_ov003_0225f278[];
extern u8 data_ov003_0223c014[];
extern void func_0205510c(char *p, Vec3 *v);

int func_ov003_0222853c(void)
{
    Vec3 v1;
    Vec3 v2;
    char *rec = data_ov003_0225f76c;
    int i = 0;
    do {
        if (*(int *) (rec + 0x80) == 3) {
            u8 *e = &data_ov003_0223c014[*(u8 *) (rec + 0x1ff) * 0x14];
            char *p;
            char *q;
            int f;
            v1.x = (e[0xe] << 12) / 100;
            v1.y = 0x1000;
            v1.z = (e[0xf] << 12) / 100;
            p = *(char **) (rec + 0x1a0);
            p = p + *(int *) (p + 8);
            q = p + *(u16 *) (p + 0xa);
            q = p + *(int *) (q + 8);
            f = *(u8 *) (rec + 0x1fd);
            if (q != 0 && f > 0) {
                *(int *) (q + 0xc) = *(int *) (q + 0xc) & 0xffe0ffff;
                *(int *) (q + 0xc) = *(int *) (q + 0xc) | ((f & 0x1f) << 16);
            }
            func_0205510c(rec + 0x144, &v1);
            if (*(u8 *) (rec + 0x7f)) {
                v2.x = (e[0xe] << 12) / 100;
                v2.y = 0x1000;
                v2.z = (e[0xf] << 12) / 100;
                func_0205510c(data_ov003_0225f278, &v2);
            }
        }
        rec += 0x24c;
        i++;
    } while (i < 6);
    return 1;
}
