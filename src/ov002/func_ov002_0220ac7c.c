/* func_ov002_0220ac7c @ 0x0220ac7c, 0x48 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov002_0220b338();
extern void func_ov002_0220b36c();
extern void *data_ov002_0220be68;
extern void *data_ov002_0220bdc0;

int func_ov002_0220ac7c(char *self)
{
    func_ov002_0220b36c(self + 0x4, &data_ov002_0220be68, 0xc, 0x3);
    func_ov002_0220b338(self + 0x4, 0x20);
    func_ov002_0220b36c(self + 0x80, &data_ov002_0220bdc0, 0x6, 0x1);
    func_ov002_0220b338(self + 0x80, 0x21);
    *(u8 *) (self + 0x1c8) = 0x2;
    return 0x1c8;
}
