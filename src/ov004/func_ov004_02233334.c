/* func_ov004_02233334 @ 0x02233334, 0x148 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 sec, min, hour, day, mon;
    u8 pad_05[3];
} Tm;
typedef union {
    Tm t;
    u32 w[2];
} TmBuf;

extern u8 func_020b65c4(void);
extern void func_0209e474(TmBuf *);
extern void func_0200467c(int);
extern u8 data_ov004_022478f0[];

int func_ov004_02233334(u8 *self)
{
    TmBuf tm;
    u8 k = func_020b65c4();
    tm.w[0] = 0;
    tm.w[1] = 0;
    func_0209e474(&tm);
    if (k < 0x33 && data_ov004_022478f0[k] != 0) {
        if (tm.t.mon == 0xc && tm.t.day == 0x1f) {
            u32 rem = 0x15180 - (tm.t.sec + (tm.t.min * 0x3c + tm.t.hour * 0xe10));
            u32 h = rem / 0xe10;
            u32 m;
            rem -= h * 0xe10;
            m = rem / 0x3c;
            rem -= m * 0x3c;
            self[0x51] = rem % 10;
            if (self[0x51] != self[0x50]) {
                if (h == 0) {
                    if (m == 1 && rem == 0) {
                        if (self[0x52] == 0) {
                            func_0200467c(0x62);
                        }
                    } else if (m == 0) {
                        if (rem == 0) {
                            if (self[0x52] == 0) {
                                func_0200467c(0x61);
                            }
                        } else if (rem <= 10) {
                            if (self[0x52] == 0) {
                                func_0200467c(0x60);
                            }
                        } else {
                            if (self[0x52] == 0) {
                                func_0200467c(0x62);
                            }
                        }
                    }
                    self[0x52] = 0;
                }
            }
            self[0x50] = self[0x51];
        } else if (tm.t.mon == 1 && tm.t.day == 1 && tm.t.hour == 0 && tm.t.min == 0 && tm.t.sec == 0) {
            if (self[0x53] == 0) {
                func_0200467c(0x61);
                self[0x53] = 1;
            }
        }
    }
    return 1;
}
