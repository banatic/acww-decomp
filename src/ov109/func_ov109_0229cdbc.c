/* func_ov109_0229cdbc @ 0x0229cdbc, 0x3c bytes, Thumb, module ov109
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov109_0229c8a4(void *);
extern void func_ov109_0229c934(void *);
extern void func_ov109_0229c9f0(void *, unsigned char);
extern void func_ov002_02207fc0(void *);
extern void func_ov002_02208098(void *, int);

void func_ov109_0229cdbc(void *r0)
{
    unsigned char *p = (unsigned char *) r0;
    p[0x29d1] = 0x10;
    func_ov109_0229c8a4(r0);
    func_ov002_02207fc0(r0);
    func_ov109_0229c934(r0);
    func_ov002_02208098(r0, 5);
    func_ov109_0229c9f0(r0, p[0x29d3]);
}
