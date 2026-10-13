/* func_020bfcd8 @ 0x020bfcd8, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020c00fc(void *);
extern void func_020bf590(void *);
void func_020bfcd8(void *self)
{
    unsigned int v;
    int flag;
    unsigned int mask;
    int cond;
    v = *((unsigned int *) (((char *) self) + 0xc));
    flag = 0;
    v -= 0x21;
    if (v <= 9) {
        mask = 1 << v;
        if (mask & 0x249) {
            flag = 1;
        }
        cond = ((*((unsigned int *) (((char *) self) + 0x60))) >> 0x1e) & 1;
    }
    if (!flag) {
        cond = ((*((unsigned int *) (((char *) self) + 0x60))) >> 0x1e) & 1;
        if (!cond) {
            func_020c00fc(self);
        }
    }
    func_020bf590(self);
}
