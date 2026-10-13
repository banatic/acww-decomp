/* func_ov138_0229c630 @ 0x0229c630, 0x24 bytes, Thumb, module ov138
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220a164(void *);
extern void func_ov002_02208098(void *, int);

void func_ov138_0229c630(void *self)
{
    unsigned char b;
    void *p;

    p = (char *) self + 0x98;
    func_ov002_0220a164(p);

    b = *(unsigned char *) ((char *) self + 0x8d);
    *(unsigned char *) ((char *) self + 0x94) = b;

    func_ov002_02208098(self, 0xa);
}
