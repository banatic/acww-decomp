/* func_ov002_0220ac7c @ 0x0220ac7c, 0x48 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov002_0220b338(char *self, int value);
extern void func_ov002_0220b36c(char *argument0, int argument1, unsigned char argument2, unsigned char argument3);
extern void *data_ov002_0220be68;
extern void *data_ov002_0220bdc0;

int func_ov002_0220ac7c(char *self)
{
    func_ov002_0220b36c((char *) (self + 0x4), (int) (&data_ov002_0220be68), (unsigned char) (0xc), (unsigned char) (0x3));
    func_ov002_0220b338(self + 0x4, 0x20);
    func_ov002_0220b36c((char *) (self + 0x80), (int) (&data_ov002_0220bdc0), (unsigned char) (0x6), (unsigned char) (0x1));
    func_ov002_0220b338(self + 0x80, 0x21);
    *(u8 *) (self + 0x1c8) = 0x2;
    return 0x1c8;
}
