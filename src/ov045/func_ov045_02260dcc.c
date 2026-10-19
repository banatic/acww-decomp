/* func_ov045_02260dcc @ 0x02260dcc, 0x34 bytes, Thumb, module ov045
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02016104(void *);
extern int func_0201c314(void *, void *);
extern int func_020147e0(void *, int, int);

int func_ov045_02260dcc(void *self)
{
    void *p;
    p = func_02016104((char *) self + 0x68c);
    if (p != 0) {
        func_0201c314(self, p);
    }
    func_020147e0((char *) self + 0x618, 1, 0);
    return 1;
}
