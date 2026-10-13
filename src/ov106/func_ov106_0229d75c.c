/* func_ov106_0229d75c @ 0x0229d75c, 0x34 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov106_0229ccc8(void *);
extern void func_ov106_0229cea8(void *);
extern void func_ov106_0229d028(void *, unsigned char);
extern void func_ov002_02207fc0(void *);
extern void func_ov002_02208098(void *, int);

void func_ov106_0229d75c(void *r0)
{
    unsigned char *p;
    unsigned char *q;

    p = (unsigned char *) r0;
    q = p + 0xb6;
    *q = 0x20;
    func_ov106_0229ccc8(r0);
    func_ov002_02207fc0(r0);
    func_ov106_0229cea8(r0);
    func_ov002_02208098(r0, 7);
    q = p + 0xb8;
    func_ov106_0229d028(r0, *q);
}
