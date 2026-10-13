/* func_ov002_02208850 @ 0x02208850, 0x18 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov002_0220bb04;
extern void func_020edb3c(void *);

void *func_ov002_02208850(void *p)
{
    *(void **) p = (void *) &data_ov002_0220bb04;
    func_020edb3c(p);
    return p;
}
