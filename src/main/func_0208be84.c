/* func_0208be84 @ 0x0208be84, 0xc4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 pad_00[2];
    u16 unk_02;
} GStructT;

extern GStructT data_021fbe40;
extern u8 data_021fbdd8, data_021fbddc, data_021f6c60, data_021f6c5c;

extern int func_020a7e50(void);
extern int func_020a7ffc(void);
extern int func_020a7e44(void);
extern int func_020a812c(void);
extern int func_0208c5f0(u8 *p);

int func_0208be84(u8 *self, int p1)
{
    int result = 0;
    int guard = result;

    if (self[0x24] != 0) {
        if (func_020a7e50() != 0) {
            if (func_020a7ffc() != 0) {
                guard = 1;
            }
        } else {
            if (func_020a7e44() != 0 && func_020a812c() != 0) {
                guard = 1;
            }
        }
    }

    if (guard == 0 && func_0208c5f0(self + 0x28) != 0) {
        u16 f2 = data_021fbe40.unk_02;

        if ((f2 & 0x400) != 0 || (p1 != 0 && (f2 & 2) != 0)) {
            result = 1;
            self[0x25] = 1;
        } else {
            unsigned int cond = (data_021fbdd8 != 0 && data_021fbddc != 0) ? 1 : 0;
            if (cond > 0) {
                u8 v5 = data_021f6c60;
                u8 v6 = data_021f6c5c;
                if ((int) v6 < 0x10 && (int) v5 >= 0xc8 && (int) v5 < 0xe8) {
                    result = 1;
                    self[0x25] = 0;
                }
            }
        }
    }

    return result;
}
