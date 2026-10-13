/* func_ov003_0220f478 @ 0x0220f478, 0x30 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Triple;

extern void func_ov003_0220f4f0(void *a, Triple *b);
extern void func_ov003_0220f538(void *a, Triple b, int c, int d);

void func_ov003_0220f478(void *s, int val)
{
    Triple t;
    func_ov003_0220f4f0((char *) s + 0x8f0, &t);
    func_ov003_0220f538(s, t, 6, val);
}
