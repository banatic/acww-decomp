/* func_ov132_0229b184 @ 0x0229b184, 0x2c bytes, Thumb, module ov132
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov132_0229ae90(void *);
extern void func_ov002_022080a0(void *, int);

void func_ov132_0229b184(unsigned char *self)
{
    if (self[0x1506]) {
        self[0x1506] = self[0x1506] - 1;
    } else {
        func_ov132_0229ae90(self);
        func_ov002_022080a0(self, 1);
    }
}
