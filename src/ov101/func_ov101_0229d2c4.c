/* func_ov101_0229d2c4 @ 0x0229d2c4, 0x38 bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *);
extern void *func_ov002_0220a720(void *, int);
extern unsigned char *func_ov002_02208098(void *, unsigned char value);
extern void RtcSendPxiCommand(int);

void func_ov101_0229d2c4(void *r0)
{
    if (func_0208e484((char *) r0 + 0x229c)) {
        func_ov002_0220a720((char *) r0 + 0x2810, 9);
        func_ov002_02208098(r0, 0x17);
        RtcSendPxiCommand(0x28);
    }
}
