/* func_ov112_022a097c @ 0x022a097c, 0x3c bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021fbe40;
extern int func_ov002_0220a568(void *ptr);
extern unsigned char *func_ov002_02208098(void *ptr, unsigned char value);
extern void func_ov112_0229f784(void);
extern void func_ov112_0229f92c(void *ptr);

void func_ov112_022a097c(void *param)
{
    if ((data_021fbe40 & 1) == 0) {
        func_ov002_0220a568((char *) param + 0x4234);
        func_ov002_02208098(param, 0x12);
        asm {
            mov r0, param
        }
        func_ov112_0229f784();
    } else {
        func_ov112_0229f92c(param);
    }
}
