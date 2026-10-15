/* func_ov049_022611f8 @ 0x022611f8, 0x2c bytes, Thumb, module ov049
 * mwccarm 1.2/base -O4,s
 */

extern void func_020157d4(void *obj, unsigned int address, unsigned char state, unsigned char flags);
extern int func_02015828(void *a, int b);
extern void func_ov049_022610c4(void *a, int b);
extern unsigned short func_ov049_02261224(void *unused0, int unused1);

void func_ov049_022611f8(void *param0, int param1)
{
    if (param1 == 0) {
        func_020157d4(param0, (unsigned int) func_ov049_02261224, 13, 0);
        func_02015828(param0, 0);
        func_ov049_022610c4(param0, 9);
    }
    return;
}
