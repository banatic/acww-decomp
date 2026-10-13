/* func_ov133_0229b3f8 @ 0x0229b3f8, 0x54 bytes, Thumb, module ov133
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov133_0229b280(char *self);
extern void func_ov130_02299dbc(void);
extern void func_ov133_0229b1e8(char *self, int x);
extern int func_ov133_0229b0f0(char *self, int x);
extern void func_0200457c(int x);
extern const u8 data_ov133_0229c790[];

int func_ov133_0229b3f8(char *self, int flag)
{
    u8 s = *(u8 *) (self + 0x9c);

    switch (s) {
        case 0xb:
            if (flag) {
                func_ov133_0229b280(self);
                func_ov130_02299dbc();
            }
            *(u8 *) (self + 0x9d) = 0;
            return 0;
        case 0xa:
            func_ov133_0229b1e8(self, 1);
            return 1;
        default:
            if (s <= 9) {
                if (func_ov133_0229b0f0(self, data_ov133_0229c790[s])) {
                    func_0200457c(0);
                }
            }
            return 1;
    }
}
