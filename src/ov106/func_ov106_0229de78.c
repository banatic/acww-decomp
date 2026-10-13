/* func_ov106_0229de78 @ 0x0229de78, 0x48 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209f70(void *);
extern void func_ov106_0229cd20(void *, unsigned char);
extern void func_ov106_0229c354(void *, int);
extern void func_ov002_02208098(void *, int);
extern void func_ov106_0229cea8(void *);

void func_ov106_0229de78(void *self)
{
    if (func_ov002_02209f70((char *) self + 0x22a0) == 0) {
        func_ov106_0229cd20(self, ((unsigned char *) self)[0xba]);
        func_ov106_0229c354(self, 0x40);
        func_ov002_02208098(self, 0x14);
        func_ov106_0229cea8(self);
    } else {
        func_ov002_02208098(self, 7);
    }
}
