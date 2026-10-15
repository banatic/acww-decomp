/* func_ov122_022a0d84 @ 0x022a0d84, 0x68 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern void func_02051bf8(void *, int);
extern void func_02051c08(int, void *, int);
extern int func_ov122_0229f634(void *);
extern void func_ov122_0229efd8(void *, int);
extern void func_ov095_022999f4(void *receiver);
extern void func_ov122_022a14c0(void *);
extern int func_ov122_0229f958(void *);

void func_ov122_022a0d84(char *self)
{
    unsigned char a, b;
    int min, diff;
    int result;

    if (func_ov122_0229f958(self) == 0) {
        return;
    }
    b = *(unsigned char *) (self + 0xae);
    a = *(unsigned char *) (self + 0xad);
    if (a > b) {
        min = b;
        diff = a - b;
    } else {
        min = a;
        diff = b - a;
    }
    func_02051bf8(self + 0x4230, 0x40);
    result = func_ov122_0229f634(self);
    func_02051c08(result + 2 * min, self + 0x4230, diff);
    func_ov122_0229efd8(self, 0x400);
    func_ov095_022999f4(self + 0xc0);
    func_ov122_022a14c0(self);
}
