/* func_020b1d88 @ 0x020b1d88, 0xcc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b65c4(void);
extern int func_02031930(void *);
extern int func_020b6744(int);
extern int func_020b67e8(int);
extern int func_020b67c0(int);
extern int func_020b66ec(int);
extern int func_020b1d18(int);
extern int func_020b6598(void);
extern unsigned char data_020e54a8;

int func_020b1d88(void *self)
{
    int call1;
    int r4;
    unsigned int flag;

    call1 = func_020b65c4();
    r4 = func_02031930(self);
    if (r4 == 0xffff) {
        flag = data_020e54a8 == 0;
        if (flag > 0) {
            r4 = 0xc8;
        } else if (func_020b6744(call1)) {
            r4 = func_020b1d18(5);
        } else if (func_020b67e8(call1) || func_020b67c0(call1)) {
            r4 = func_020b1d18(6);
        } else if (func_020b66ec(call1)) {
            r4 = func_020b1d18(5);
        } else {
            r4 = 0x4a6;
        }
    }
    if (r4 == 0xc0) {
        if (func_020b6598()) {
            unsigned int flag2 = data_020e54a8 == 0;
            if (flag2 != 0) {
                goto set877;
            }
            {
                int cond = 1;
                unsigned char x = (unsigned char) (call1 + 0xf5);
                if (x > 3 && call1 != 0x2f) {
                    cond = 0;
                }
                if (!cond) {
                    goto done;
                }
            }
        set877:
            r4 = 0x877;
        done:;
        }
    }
    return r4;
}
