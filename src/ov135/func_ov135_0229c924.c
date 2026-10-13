/* func_ov135_0229c924 @ 0x0229c924, 0x30 bytes, Thumb, module ov135
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov135_0229c738(void);
extern void func_ov134_0229a5c8(char *, int);
extern void func_ov002_02208098(void *, int);
extern void func_0206f768(void);

void func_ov135_0229c924(void *obj, int arg)
{
    func_ov135_0229c738();
    func_ov134_0229a5c8((char *) obj + 0x2c8, arg);
    func_ov002_02208098(obj, 0xe);
    func_0206f768();
}
