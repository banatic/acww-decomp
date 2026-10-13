/* func_ov068_02272df0 @ 0x02272df0, 0x38 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void func_0203e328(void);
extern void func_020b22c4(void);
extern void func_020b22e8(void);

int func_ov068_02272df0(void *arg0)
{
    if (*(unsigned int *) ((char *) arg0 + 0x2b4) != 0) {
        func_0203e328();
    }
    if (*(unsigned char *) ((char *) arg0 + 0x2de) != 0) {
        *(unsigned char *) ((char *) arg0 + 0x2de) = 0;
        func_020b22c4();
        func_020b22e8();
    }
    return 1;
}
