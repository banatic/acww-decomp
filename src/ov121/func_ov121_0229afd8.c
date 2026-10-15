/* func_ov121_0229afd8 @ 0x0229afd8, 0x30 bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov121_0229a3fc(void *);
extern void func_ov121_0229a450(void *);
extern void func_ov002_02207fc0(void *);
extern unsigned char *func_ov002_02208098(void *, unsigned char value);

unsigned char *func_ov121_0229afd8(void *param)
{
    unsigned char *p = (unsigned char *) param;
    p[0xae] = 0x18;
    p[0xad] = 0x18;
    func_ov121_0229a3fc(param);
    func_ov002_02207fc0(param);
    func_ov121_0229a450(param);
    return func_ov002_02208098(param, 4);
}
