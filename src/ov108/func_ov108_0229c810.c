/* func_ov108_0229c810 @ 0x0229c810, 0x54 bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov108_0229c7c8(void *);
extern void *func_ov108_0229c7b8(void *);
extern void func_ov108_0229c5d4(void *);
extern void func_ov002_0220a0b4(void *, void *, void *);
extern void func_ov002_0220a374(void *, unsigned int);

void func_ov108_0229c810(unsigned char *self)
{
    void *p1;
    void *p2;
    p1 = func_ov108_0229c7c8(self);
    p2 = func_ov108_0229c7b8(self);
    func_ov002_0220a0b4(self + 0x2498, p1, p2);
    if (self[0x2b0] == 0x15) {
        func_ov002_0220a374(self + 0x2498, 7);
    } else {
        func_ov002_0220a374(self + 0x2498, 1);
    }
    func_ov108_0229c5d4(self);
}
