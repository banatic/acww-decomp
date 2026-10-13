/* func_ov004_02237218 @ 0x02237218, 0x15c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

class Actor;
typedef void (Actor::*Method)();
extern "C" Method data_ov004_0225949c[];
extern "C" unsigned char *data_ov004_022594d4[];
extern "C" int func_020ea9e4(void *, void *);
extern "C" void func_ov004_02239700(void *);
extern "C" void func_ov004_02239524(void *, int);
extern "C" void func_ov004_0223592c(void *);
extern "C" int func_ov004_02239424(void *, void *, void *, int);
extern "C" unsigned int func_ov004_02239460(int, int);
extern "C" void func_ov004_0223635c(void *, void *);
extern "C" void func_ov004_02237094(void *);
extern "C" void func_ov004_022370f4(void *);
extern "C" void func_ov004_02237218(unsigned char *self)
{
    if (func_020ea9e4(self + 0x1a8, self + 0x258) <= 0x1000) {
        self[0x255] = 1;
    } else {
        self[0x255] = 0;
    }
    if (self[0x256] == 0) {
        if (self[0x1ee] != 2 && self[0x1ee] != 6) {
            func_ov004_02239700(self);
            func_ov004_02239524(self, 0x1554);
        }
        (((Actor *) self)->*data_ov004_0225949c[self[0x1ee]])();
        func_ov004_0223592c(self);
        if (func_ov004_02239424(self + 0x1c0, self + 0x1a8, self + 0x258, 0x1000)) {
            if (*(unsigned int *) (self + 0x278) >= *(unsigned int *) (self + 0x274)) {
                *(unsigned int *) (self + 0x278) = 0;
                self[0x256] = 1;
                *(unsigned int *) (self + 0x274) = func_ov004_02239460(200, 320);
            }
            unsigned int other = self[0x1e8];
            if (self[0x252] != other && other != *(unsigned int *) (self + 0x15c)) {
                self[0x252] = other;
                self[0x256] = 2;
            }
        } else {
            unsigned int other = self[0x1e8];
            if (self[0x252] != other && other != *(unsigned int *) (self + 0x15c)) {
                self[0x252] = other;
                if (self[0x1ee] != 1) {
                    func_ov004_0223635c(self, data_ov004_022594d4[self[0x1e8]] + 0x1a8);
                }
            }
        }
        ++*(unsigned int *) (self + 0x278);
    } else {
        func_ov004_02237094(self);
    }
    func_ov004_022370f4(self);
}
