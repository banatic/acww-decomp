/* func_ov116_0229e41c @ 0x0229e41c, 0x38 bytes, Thumb, module ov116
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov116_0229deb4(void *);
extern void func_ov002_02207f04(void *, int, int, int, int);
extern void func_ov116_0229e3a8(void *);
extern void func_ov002_02208090(void *, int);
extern void func_ov114_0229c8b4(void *);

void func_ov116_0229e41c(void *p)
{
    func_ov116_0229deb4(p);
    func_ov002_02207f04(p, 0xb, 0, 0, 0x30);
    func_ov116_0229e3a8(p);
    func_ov002_02208090(p, 3);
    p = (void *) ((char *) p + 0xf8);
    func_ov114_0229c8b4(p);
}
