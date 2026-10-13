/* func_ov004_02221910 @ 0x02221910, 0x3c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_0200366c();
extern int func_020644cc();
extern int func_0208150c();
extern void *data_ov004_02254094;
extern void *data_ov004_02257f20;

int func_ov004_02221910(char *self, char *a1)
{
    // DECLS
    int v1;
    int v5;
    // ENDDECLS
    v1 = *(int *) (self + 0x1a4);
    func_0200366c(func_0208150c(*(int *) ((char *) v1 + 0x830), v1), &data_ov004_02257f20, 0x28, &data_ov004_02254094);
    *(void **) (a1) = &data_ov004_02257f20;
    v5 = func_020644cc(0x5);
    *(u8 *) (a1 + 0x4) = v5;
    return v5;
}
