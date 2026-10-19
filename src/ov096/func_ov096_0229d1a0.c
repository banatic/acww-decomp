/* func_ov096_0229d1a0 @ 0x0229d1a0, 0x34 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200467c(int);
extern void func_ov096_0229dc48(void *);
extern void func_ov002_022096d8(void *, int);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov096_0229d1a0(void *p)
{
    func_0200467c(0x2a);
    ((unsigned char *) p)[0xbb] = 0x22;
    func_ov096_0229dc48(p);
    func_ov002_022096d8((char *) p + 0x2564, 0);
    func_ov002_02208098((void *) (p), 0x1f);
}
