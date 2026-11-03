/* tarot_object_2: 3 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02230978 @ 0x02230978, 0x4 bytes, Thumb
 * func_ov004_022308dc @ 0x022308dc, 0x9c bytes, Thumb
 * func_ov004_022308a8 @ 0x022308a8, 0x34 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int m[12];
} Mtx;

extern Mtx *func_ov045_02260630(void);
extern void func_0205510c(void *, int);
extern Mtx data_021fbe48;
extern void func_ov004_0222c598(void *);
extern void func_ov004_02230404(void *, int);
extern void *data_ov004_02258870;

int func_ov004_02230978(void)
{
    return 1;
}

void func_ov004_022308dc(char *self)
{
    u8 i;
    char *b;
    int z;
    data_021fbe48 = *func_ov045_02260630();
    *(Mtx *) (self + 0x150) = data_021fbe48;
    *(Mtx *) (self + 0x2f4) = data_021fbe48;
    if (*(u8 *) (self + 0x6d4) != 0) {
        func_0205510c(self + 0xec, 0);
    }
    i = 0;
    b = self + 0x290;
    z = i;
    do {
        if (*(u8 *) (self + i + 0x6b0) != 0) {
            func_0205510c(b + i * 0xb8, z);
        }
        i = (u8) (i + 1);
    } while (i < 3);
}

int func_ov004_022308a8(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0222c598(self);
    func_ov004_02230404(self, 0x0);
    func_ov004_02230404(self, 0x1);
    func_ov004_02230404(self, 0x2);
    *(void **) ((char *) &data_ov004_02258870) = 0x0;
    return 0x1;
}
