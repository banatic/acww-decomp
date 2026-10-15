/* func_ov141_0229a358 @ 0x0229a358, 0x2c bytes, Thumb, module ov141
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220a164(void *);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov141_0229a358(void *this)
{
    unsigned char *self = (unsigned char *) this;
    func_ov002_0220a164(self + 0xa38);
    self[0x1a7e] = self[0x8d];
    func_ov002_02208098((void *) (this), 4);
}
