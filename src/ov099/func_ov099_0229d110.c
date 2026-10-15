/* func_ov099_0229d110 @ 0x0229d110, 0x3c bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov099_0229c7d0(void *);
extern void func_ov099_0229c9d0(void *);
extern void func_ov099_0229cb8c(void *, unsigned char);
extern void func_ov002_02207fc0(void *);
extern unsigned char *func_ov002_02208098(void *, unsigned char value);

void func_ov099_0229d110(void *p)
{
    ((unsigned char *) p)[0x2905] = 0x1d;
    func_ov099_0229c7d0(p);
    func_ov002_02207fc0(p);
    func_ov099_0229c9d0(p);
    func_ov002_02208098(p, 4);
    func_ov099_0229cb8c(p, ((unsigned char *) p)[0x2907]);
}
