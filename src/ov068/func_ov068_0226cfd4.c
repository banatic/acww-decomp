/* func_ov068_0226cfd4 @ 0x0226cfd4, 0x48 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_02019e00(char *arg);
extern int func_02019df8(char *arg);
extern void *func_02018fdc(int arg);
extern void func_0201a698(void *, void *, int);

void func_ov068_0226cfd4(char *p)
{
    void *q;

    if (func_02019e00(p + 0x564) == 8) {
        if (func_02019df8(p + 0x564) != 0) {
            q = func_02018fdc(0);
            if (q != 0) {
                ((unsigned char *) p)[0x445] = 0;
                func_0201a698(p + 0x420, q, 0);
            }
        }
    }
}
