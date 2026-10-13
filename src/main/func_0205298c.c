/* func_0205298c @ 0x0205298c, 0xb0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b65c4(int, int, int, int);
extern int func_ov004_0223cd50(void);
extern int func_ov004_0223cc10(int, int, int, int);
extern int func_ov004_0220d2b8(int);
extern unsigned func_ov004_0223c264(void *);
extern int func_ov004_0223c1ec(void *, int);
extern void func_02052738(int, int, int, int);
extern void func_020526b8(int, int, int, int, int, int, int);
extern unsigned char data_020e54a8;

extern void func_ov004_02211280(void);

void func_0205298c(int a0, int a1, int a2, int a3, unsigned char a4)
{
    int r;
    int ret;
    unsigned int flag;

    if (func_020b65c4(a0, a1, a2, a3) != a0) {
        return;
    }

    flag = (data_020e54a8 == 1) ? 1 : 0;
    if (flag > 0) {
        r = func_ov004_0223cc10(func_ov004_0223cd50(), a1, a2, a3);
        if (r != 0) {
            if (func_ov004_0220d2b8(r + 0x740) == 0) {
                if (func_ov004_0223c264((void *) func_ov004_02211280) >= 4) {
                    ret = func_ov004_0223c1ec((void *) func_ov004_02211280, 0);
                    if (ret != 0) {
                        func_02052738(ret, 0, 0xff, a4);
                    }
                }
                func_020526b8(a1, a2, a3, 1, 0xff, a4, 1);
            } else {
                func_020526b8(a1, a2, a3, 0, 0xff, a4, 1);
            }
        }
    }
}
