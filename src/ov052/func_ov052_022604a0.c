/* func_ov052_022604a0 @ 0x022604a0, 0x4c bytes, Thumb, module ov052
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203ec98(void);
extern void func_0209e474(void *);
extern void func_ov052_022610cc(void *ptr, int arg);
extern int func_0203e0a8(void *self, int arg);

int func_ov052_022604a0(void *self)
{
    int buf[2];

    if (func_0203ec98() != 0) {
        return 0;
    }
    buf[0] = 0;
    buf[1] = 0;
    func_0209e474(buf);
    if (((unsigned char *) buf)[2] < 6) {
        func_ov052_022610cc((char *) self + 0x658, 0xc);
        func_0203e0a8(self, 0);
        return 1;
    }
    return 0;
}
