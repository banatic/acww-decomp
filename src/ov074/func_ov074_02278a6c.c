/* func_ov074_02278a6c @ 0x02278a6c, 0x22 bytes, Thumb, module ov074
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b9e2c(void *p);
extern void func_020e993c(const void *heap, void *block);

struct unknown_struct {
    int x;
    int y;
};

void func_ov074_02278a6c(struct unknown_struct *a, const void *b)
{
    func_020b9e2c(&a->y);
    if (a->x != 0) {
        func_020e993c(b, (void *) a->x);
    }
}
