/* func_ov111_0229f24c @ 0x0229f24c, 0x3c bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov111_0229f660(void *p);
extern void func_ov111_0229f1d8(void *p);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

extern unsigned char data_021fbe40[];

int func_ov111_0229f24c(void *param)
{
    unsigned short *reg = (unsigned short *) data_021fbe40;
    if ((reg[1] & 8) == 0) {
        return 0;
    }
    if (func_ov111_0229f660(param) != 0) {
        func_ov111_0229f1d8(param);
        func_ov002_02208098((void *) (param), 13);
        return 1;
    }
    return 0;
}
