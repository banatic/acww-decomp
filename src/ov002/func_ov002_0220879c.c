/* func_ov002_0220879c @ 0x0220879c, 0x20 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov002_0220baf4;
extern void func_ov002_02208844(void *);
extern void func_020edb3c(void *);

void *func_ov002_0220879c(void *p)
{
    *(void **) p = &data_ov002_0220baf4;
    func_ov002_02208844(p);
    func_020edb3c(p);
    return p;
}
