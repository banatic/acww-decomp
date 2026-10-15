/* func_ov140_0229a85c @ 0x0229a85c, 0x38 bytes, Thumb, module ov140
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov140_0229a164(unsigned char *param, unsigned char value);
extern void func_ov140_0229a280(unsigned char *param);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov140_0229a85c(unsigned char *param)
{
    unsigned char *p = param;
    p += 0x8db;
    if (*p > 1) {
        *p = *p - 1;
        func_ov140_0229a164(param, *p);
    } else {
        func_ov140_0229a164(param, 0);
        func_ov140_0229a280(param);
        func_ov002_02208098((void *) (param), 7);
    }
}
