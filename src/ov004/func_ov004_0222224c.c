/* func_ov004_0222224c @ 0x0222224c, 0x16c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

#define P(p, o) (*(u8 **) ((p) + (o)))
extern u8 data_ov004_02257fc4[], data_ov004_02254298[], data_ov004_022542a4[];
extern void *func_0206837c(void *), *func_0208150c(void *);
extern int func_020ab504(void *), func_020644cc(int), func_ov004_02222a30(u16 *, int);
extern u16 func_0206f9d8(int (*)(u16 *, int));
extern void func_0200366c(void *, void *, int, void *), func_0206844c(void *, u8 *, void *);
void func_ov004_0222224c(u8 *self)
{
    u8 messages[6];
    int choice = func_020ab504(func_0206837c(P(P(self, 0x1a8), 0x8e0)));
    if (P(self, 0x1a8)[0x897] == 0) {
        func_0200366c(func_0208150c(P(P(self, 0x1a8), 0x830)), data_ov004_02257fc4, 40, data_ov004_02254298);
        P(self, 0x1a8)[0x899] = 1;
    } else {
        func_0200366c(func_0208150c(P(P(self, 0x1a8), 0x830)), data_ov004_02257fc4, 40, data_ov004_022542a4);
        P(self, 0x1a8)[0x899] = 1;
    }
    if (P(self, 0x1a8)[0x898] == 0) {
        switch (choice) {
            case 0:
                if (func_0206f9d8(func_ov004_02222a30)) {
                    messages[0] = func_020644cc(3) + 7;
                    func_0206844c(P(P(self, 0x1a8), 0x8e0), &messages[0], data_ov004_02257fc4);
                } else {
                    messages[1] = func_020644cc(3) + 10;
                    func_0206844c(P(P(self, 0x1a8), 0x8e0), &messages[1], data_ov004_02257fc4);
                }
                break;
            case 1:
                messages[2] = func_020644cc(4);
                func_0206844c(P(P(self, 0x1a8), 0x8e0), &messages[2], data_ov004_02257fc4);
                break;
            default:
                messages[3] = func_020644cc(3) + 4;
                func_0206844c(P(P(self, 0x1a8), 0x8e0), &messages[3], data_ov004_02257fc4);
                break;
        }
    } else if (choice == 0) {
        messages[4] = func_020644cc(3) + 19;
        func_0206844c(P(P(self, 0x1a8), 0x8e0), &messages[4], data_ov004_02257fc4);
    } else {
        messages[5] = func_020644cc(3) + 4;
        func_0206844c(P(P(self, 0x1a8), 0x8e0), &messages[5], data_ov004_02257fc4);
    }
}
