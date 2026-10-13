/* func_ov004_02236594 @ 0x02236594, 0x134 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

class Actor {};
typedef void (Actor::*Method)();
extern "C" {
extern Method data_ov004_0225949c[];
extern unsigned char data_ov004_02247924[];
extern unsigned char *data_ov004_022594d4[];
extern void func_ov004_0223635c(void *, void *);
extern void func_ov004_02239b80(void *);
extern int func_ov004_02239768(void *);
extern void func_ov004_022395d0(void *, int, int);
extern void func_ov004_022396a0(void *);
extern void func_ov004_0223592c(void *);
extern void func_ov004_022358c0(void *, int);
extern int func_ov004_02236418(void *);
void func_ov004_02236594(unsigned char *self)
{
    (((Actor *) self)->*data_ov004_0225949c[self[0x1ee]])();
    {
        int id = *(int *) (self + 0x15c);
        if (data_ov004_02247924[id * 17] == 0) {
            unsigned char *encounter = self + 0x1e8;
            unsigned char previous = *encounter;
            if (self[0x252] != previous && previous != id) {
                self[0x252] = previous;
                if (self[0x1ee] != 1) {
                    func_ov004_0223635c(self, data_ov004_022594d4[*encounter] + 0x1a8);
                }
            }
        }
    }
    func_ov004_02239b80(self);
    if (!(self[0x1ee] == 5 && *(int *) (self + 0x20c) < 205) && self[0x1ee] != 6) {
        int id;
        func_ov004_02239768(self);
        id = *(int *) (self + 0x15c);
        if (id == 29) {
            func_ov004_022395d0(self, 0xe38, 0x4b0);
        } else {
            unsigned char kind = data_ov004_02247924[id * 17];
            if (kind == 0) {
                func_ov004_022396a0(self);
            } else if (kind >= 4) {
                func_ov004_022395d0(self, 0x71c, 0x384);
            } else {
                func_ov004_022395d0(self, 0x1554, 0x384);
            }
        }
        func_ov004_0223592c(self);
    }
    func_ov004_022358c0(self, 0x333);
    ++*(int *) (self + 0x158);
    func_ov004_02236418(self);
}
}
