/* func_ov004_02221910 @ 0x02221910, 0x3c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_0200366c(int argument0, int argument1, int argument2, int argument3);
extern int func_020644cc(int argument0);
extern int func_0208150c(unsigned int argument0);
extern void *data_ov004_02254094;
extern void *data_ov004_02257f20;

int func_ov004_02221910(char *self, char *a1)
{
    // DECLS
    int v1;
    int v5;
    // ENDDECLS
    v1 = *(int *) (self + 0x1a4);
    func_0200366c((int) (func_0208150c((unsigned int) ((unsigned int) (*(int *) ((char *) v1 + 0x830))))),
                  (int) (&data_ov004_02257f20), (int) (0x28), (int) (&data_ov004_02254094));
    *(void **) (a1) = &data_ov004_02257f20;
    v5 = func_020644cc(0x5);
    *(u8 *) (a1 + 0x4) = v5;
    return v5;
}
