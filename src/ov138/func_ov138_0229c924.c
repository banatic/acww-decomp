/* func_ov138_0229c924 @ 0x0229c924, 0x2c bytes, Thumb, module ov138
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov138_0229c738(void);
extern void func_ov134_0229a5c8(void *p, void *q);
extern void func_ov002_02208098(void *p, int n);

void func_ov138_0229c924(void *r0, void *r1)
{
    void *r5 = r0;
    void *r4 = r1;
    func_ov138_0229c738();
    func_ov134_0229a5c8((char *) r5 + 0x2c8, r4);
    func_ov002_02208098(r5, 0xc);
}
