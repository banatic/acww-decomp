/* func_ov131_0229b188 @ 0x0229b188, 0x40 bytes, Thumb, module ov131
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021fbe40;
extern void func_ov130_0229a24c(void *p);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov131_0229aee4(void *p);
extern int func_ov130_0229a224(void *p);

void func_ov131_0229b188(void *p)
{
    if ((data_021fbe40 & 1) == 0) {
        func_ov130_0229a24c((char *) p + 0x2c4);
        func_ov002_02208098((void *) (p), 2);
        func_ov131_0229aee4(p);
    } else {
        func_ov130_0229a224((char *) p + 0x2c4);
    }
}
