/* func_ov048_02262e94 @ 0x02262e94, 0x54 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a13a0(void);
extern int func_020b5e10(void);
extern int func_020b6098(int, int);
extern void func_ov048_022635f4(void *, int);
extern unsigned char data_021c75b8;
int func_ov048_02262e94(void *r0)
{
    char *ptr;
    ptr = (char *) r0;
    if ((*((unsigned int *) (ptr + 0x654))) == 8) {
        int cond = (data_021c75b8) ? (0) : (1);
        if (cond != 0) {
            func_020a13a0();
        } else {
            return 0;
        }
        func_ov048_022635f4(r0, 3);
    } else {
        func_020b6098(func_020b5e10(), 0);
        func_ov048_022635f4(r0, 3);
    }
    return 1;
}
