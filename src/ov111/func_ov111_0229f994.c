/* func_ov111_0229f994 @ 0x0229f994, 0x40 bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov111_0229f4c4(void *);
extern void func_ov111_0229efec(void *);
extern void func_02051bf8(void *, int);
extern void func_ov095_0229cd30(void *);

void func_ov111_0229f994(void *self)
{
    char *p;
    char *q;
    char *r;
    char *s;

    p = (char *) self + 0x9c;
    *p = 0x10;
    q = (char *) self + 0xa1;
    *q = 0;
    r = (char *) self + 0x9e;
    *r = 0;
    func_ov111_0229f4c4(self);
    func_ov111_0229efec(self);
    s = (char *) self + 0xac;
    func_ov095_0229cd30(s);
    func_02051bf8((char *) self + 0x3d16, 0x10);
}
