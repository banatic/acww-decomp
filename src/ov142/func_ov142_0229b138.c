/* func_ov142_0229b138 @ 0x0229b138, 0x3c bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov142_0229af94(void *);
extern void func_ov142_022999a4(void *);
extern void func_ov002_02208090(void *, int);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern void func_ov002_02207e9c(void *, int, int);
extern void func_0200467c(int);

void func_ov142_0229b138(void *p)
{
    char *q = (char *) p + 0xbf;
    *q = 7;
    func_ov142_0229af94(p);
    func_ov002_02208090(p, 4);
    func_ov002_022080a0((void *) (p), 1);
    func_ov002_02207e9c(p, 0, 0);
    func_ov142_022999a4(p);
    func_0200467c(0x59);
}
