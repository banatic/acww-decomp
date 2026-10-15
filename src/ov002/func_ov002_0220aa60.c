/* func_ov002_0220aa60 @ 0x0220aa60, 0x6c bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov002_0220b04c(char *p);
extern void func_ov002_0220b06c(char *p, void *a, int b, int c);
extern void func_0208aa68(char *p);
extern void func_ov002_0220b36c(char *argument0, int argument1, unsigned char argument2, unsigned char argument3);
extern void func_ov002_0220b338(char *self, int value);
extern void *data_ov002_0220bd38;
extern void *data_ov002_0220bd20;

int func_ov002_0220aa60(char *self, void *arg)
{
    func_ov002_0220b04c(self + 0xfc);
    func_ov002_0220b06c(self + 0xfc, arg, 0x80, 0x11);
    func_0208aa68(self + 0xfc);
    func_ov002_0220b36c((char *) (self + 0x4), (int) (&data_ov002_0220bd38), (unsigned char) (0x4), (unsigned char) (0x1));
    func_ov002_0220b338(self + 0x4, 0x4);
    func_ov002_0220b36c((char *) (self + 0x80), (int) (&data_ov002_0220bd20), (unsigned char) (0x4), (unsigned char) (0x1));
    func_ov002_0220b338(self + 0x80, 0x13);
    *(u8 *) (self + 0x1c8) = 0x8;
    return 0x1c8;
}
