/* func_ov068_0226ca74 @ 0x0226ca74, 0x38 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_021c67a4;
extern unsigned int data_021c67d0[3];
extern int func_ov068_0226caac(unsigned int, unsigned int *, char *);

int func_ov068_0226ca74(unsigned int arg0, char *arg1)
{
    char *dst = arg1 + 0x5c;
    int ret = 0;
    if (data_021c67a4 != 0) {
        unsigned int local[3];
        local[0] = data_021c67d0[0];
        local[1] = data_021c67d0[1];
        local[2] = data_021c67d0[2];
        ret = func_ov068_0226caac(arg0, local, dst);
    }
    return ret;
}
