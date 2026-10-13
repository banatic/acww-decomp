/* func_ov102_0229d760 @ 0x0229d760, 0x3c bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov102_0229cbcc(void *);
extern void func_ov102_0229cdf4(void *);
extern void func_ov102_0229cf90(void *, unsigned char);
extern void func_ov002_02207fc0(void *);
extern void func_ov002_02208098(void *, int);

void func_ov102_0229d760(void *p)
{
    ((unsigned char *) p)[0x25a1] = 0x25;
    func_ov102_0229cbcc(p);
    func_ov002_02207fc0(p);
    func_ov102_0229cdf4(p);
    func_ov002_02208098(p, 3);
    func_ov102_0229cf90(p, ((unsigned char *) p)[0x25a5]);
}
