/* func_ov004_0222cc84 @ 0x0222cc84, 0x88 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_02055050(void *);
extern void func_02055060(void *, int, int, int, int, int);
extern int func_02055140(void *, int);
extern int func_ov004_0222c3c4(void *, int);
extern int func_ov004_0222c600(void *, void *, void *);
extern int func_ov004_0222c904(void *);
extern void *data_021c9b24;
extern void *data_ov004_02254d40;
extern void *data_ov004_02254d5c;
extern void *data_ov004_02258224;

int func_ov004_0222cc84(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) ((char *) &data_ov004_02258224) = self;
    *(u8 *) (self + 0x374) = 0x0;
    func_ov004_0222c600(self, &data_ov004_02254d40, &data_ov004_02254d5c);
    func_ov004_0222c904(self);
    if (func_ov004_0222c3c4(self + 0x1a4, 0x0) != 0x0 &&
        func_02055140(self + 0xec, *(int *) ((char *) &data_021c9b24)) != 0x0) {
        func_02055060(self + 0xec, func_ov004_0222c3c4(self + 0x1a4, 0x0), 0x1, 0x1000, 0x0, 0x0);
        func_02055050(self + 0xec);
    }
    return 0x1;
}
