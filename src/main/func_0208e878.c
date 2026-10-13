/* func_0208e878 @ 0x0208e878, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

/* Constructor-style function; returns self after initialisation.
   Twin of func_0208e8d4 (identical structure, different address). */

extern void func_0208af30(void *self);
extern void func_0208a1f8(void *self);
extern void func_0208e508(void *self, int a);

extern unsigned char data_020e2314[];

void *func_0208e878(void *self, u8 a)
{
    func_0208af30(self);
    *(u32 *) ((char *) self + 0) = (unsigned int) data_020e2314;
    func_0208a1f8((char *) self + 0xc);
    *(u32 *) ((char *) self + 0x20) = 0;
    *(u32 *) ((char *) self + 0x24) = 0;
    *(u32 *) ((char *) self + 0x28) = -1;
    func_0208a1f8((char *) self + 0x2c);
    *(u32 *) ((char *) self + 0x40) = 0;
    *(u32 *) ((char *) self + 0x44) = 0x16;
    *(u8 *) ((char *) self + 0x48) = a;
    *(u8 *) ((char *) self + 0x49) = 1;
    *(u8 *) ((char *) self + 0x4a) = 0;
    func_0208e508(self, 0);
    return self;
}
