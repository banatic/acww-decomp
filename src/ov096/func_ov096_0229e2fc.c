/* func_ov096_0229e2fc @ 0x0229e2fc, 0xb4 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_02095b9c(u16 *p);
extern int func_02095b90(u16 *p);
extern int func_02095b84(u16 *p);
extern int func_02095b1c(u16 *p);
extern int func_02095aec(u16 *p);
extern int func_02095b64(void);
extern int CARD_IsEnabled(void);
extern void RtcSendPxiCommand(int a);

int func_ov096_0229e2fc(void *unused, unsigned int p, u16 x)
{
    u16 t;

    t = x;

    switch (p) {
        case 2:
            if (func_02095b9c(&t) != 0) {
                return 1;
            }
            break;
        case 3:
            if (func_02095b90(&t) != 0) {
                return 1;
            }
            break;
        case 6:
            if (func_02095b90(&t) != 0) {
                t = 0xfff1;
                func_02095b84(&t);
                return 1;
            }
            break;
        case 4:
            if (func_02095b84(&t) != 0) {
                return 1;
            }
            break;
        case 5:
            if (func_02095b1c(&t) != 0) {
                return 1;
            }
            break;
        case 7:
            if (func_02095aec(&t) != 0) {
                if (CARD_IsEnabled() == 0) {
                    RtcSendPxiCommand(0x40);
                }
                return 1;
            }
            break;
        case 8:
            if (func_02095b64() != 0) {
                return 1;
            }
            break;
    }
    return 0;
}
