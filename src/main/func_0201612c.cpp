/* func_0201612c @ 0x0201612c, 0x2e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/Base_02066994.h"

extern "C" {
void func_02016004(void *);
void func_020159f0(void *);
}

extern "C" void func_0201612c(Base_02066994 *arg0)
{
    Base_02066994 *r4 = arg0;
    r4->Base_02066994::vfunc_02066994_08();
    *(unsigned int *) ((char *) r4 + 0x48) = 0;
    *(unsigned int *) ((char *) r4 + 0x50) = 0;
    *(unsigned char *) ((char *) r4 + 0x54) = 0;
    *(unsigned char *) ((char *) r4 + 0x55) = 0;
    *(unsigned int *) ((char *) r4 + 0x5c) = 0;
    func_02016004(r4);
    func_020159f0(r4);
}
