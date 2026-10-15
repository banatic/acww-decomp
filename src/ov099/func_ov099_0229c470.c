/* func_ov099_0229c470 @ 0x0229c470, 0x30 bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov099_0229c608(void *);
extern void func_ov002_022096d8(void *, int);
extern unsigned char *func_ov002_02208098(void *, unsigned char value);

void func_ov099_0229c470(void *param)
{
    char *p = (char *) param;
    p[0x290b] = 1;
    func_ov099_0229c608(param);
    func_ov002_022096d8((char *) param + 0x22d8, 0);
    func_ov002_02208098(param, 0x13);
}
