/* func_ov119_0229a4e4 @ 0x0229a4e4, 0x28 bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov119_0229b9a4(void *);
extern void func_ov002_022096d8(void *, int);
extern unsigned char *func_ov002_02208098(void *, unsigned char value);

void func_ov119_0229a4e4(void *param)
{
    *(unsigned char *) ((char *) param + 0xad) = 0xa;
    func_ov119_0229b9a4(param);
    func_ov002_022096d8((char *) param + 0xdc, 0);
    func_ov002_02208098(param, 0xc);
}
