/* func_ov002_022089bc @ 0x022089bc, 0x18 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern void func_020edb3c(void *a, void *b);
extern int data_ov002_0220bb14;

void *func_ov002_022089bc(void *p)
{
    void *v = (void *) &data_ov002_0220bb14;
    *(void **) p = v;
    func_020edb3c(p, v);
    return p;
}
