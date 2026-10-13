/* func_ov104_0229dd20 @ 0x0229dd20, 0x34 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov104_0229d3f0(void *);
extern void func_ov104_0229d5c0(void *);
extern void func_ov104_0229d748(void *, unsigned char);
extern void func_ov002_02207fc0(void *);
extern void func_ov002_02208098(void *, int);

void func_ov104_0229dd20(void *p)
{
    unsigned char *q = (unsigned char *) p;
    q[0xb6] = 0x21;
    func_ov104_0229d3f0(p);
    func_ov002_02207fc0(p);
    func_ov104_0229d5c0(p);
    func_ov002_02208098(p, 7);
    func_ov104_0229d748(p, ((unsigned char *) p)[0xb8]);
}
