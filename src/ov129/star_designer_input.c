/* star_designer_input: 2 functions, module ov129
 * mwccarm 1.2/base -O4,s
 * func_ov129_0229c328 @ 0x0229c328, 0x20 bytes, Thumb
 * func_ov129_0229c2fc @ 0x0229c2fc, 0x2c bytes, Thumb
 */

extern void func_ov002_0220a1dc(void *);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov002_0220a164(unsigned char *p);

void func_ov129_0229c328(void *arg0)
{
    func_ov002_0220a1dc((char *) arg0 + 0x3a0);
    func_ov002_02208098((void *) (arg0), 8);
}

void func_ov129_0229c2fc(unsigned char *param)
{
    func_ov002_0220a164(param + 0x3a0);
    param[0xac] = param[0x8d];
    func_ov002_02208098((void *) (param), 9);
}
