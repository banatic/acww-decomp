/* func_020b9280 @ 0x020b9280, 0x168 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u8 data_021f6c30;
extern u8 data_021f6c34;
extern u8 data_021f6c38;
extern u8 data_021f6c3c;
extern u8 data_021f6c40;
extern u8 data_021f6c44;
extern u8 data_021f6c48;
extern u8 data_021f6c4c;
extern u8 data_021f6c50;
extern u8 data_021f6c54;
extern u8 data_021f6c58;
extern u8 data_021f6c5c;
extern u8 data_021f6c60;
extern u8 data_021f6c64;
extern u16 data_021f6c68;
extern u16 data_021f6c6c;
extern u8 data_021fbdd8;
extern u8 data_021fbddc;
extern u16 data_021fbde0;
extern u16 data_021fbde4;
#define g_027fffa8 (*(u16 *) 0x027fffa8)

extern void func_020e9314(void);
extern void func_020041ac(u8 v);

void func_020b9280(void)
{
    u8 t;
    u8 lo;
    unsigned int ok;

    data_021f6c50 = data_021f6c60;
    data_021f6c4c = data_021f6c5c;
    data_021f6c48 = data_021f6c58;
    data_021f6c44 = data_021f6c54;
    data_021f6c40 = data_021f6c30;
    data_021f6c3c = data_021f6c64;
    t = data_021fbdd8;
    data_021f6c38 = t;
    data_021f6c34 = (data_021fbddc != 0);
    data_021f6c68 = (u8) data_021fbde0;
    data_021f6c6c = (u8) data_021fbde4;
    if (((g_027fffa8 & 0x8000) >> 15) != 0) {
        data_021fbddc = t;
        data_021fbdd8 = 0;
        data_021fbde0 = 0;
        data_021fbde4 = 0;
    } else {
        func_020e9314();
    }
    if (data_021fbdd8 != 0) {
        ok = (data_021fbdd8 != 0 && data_021fbddc != 0);
        if (ok) {
            data_021f6c60 = (u8) data_021fbde0;
            data_021f6c5c = (u8) data_021fbde4;
            data_021f6c30 = 0;
        }
        if (data_021f6c30 < 0xc8) {
            data_021f6c30++;
        }
        lo = (u8) data_021fbde0;
        data_021f6c58 = lo;
        data_021f6c54 = (u8) data_021fbde4;
        func_020041ac(lo);
    } else {
        ok = (data_021fbdd8 == 0 && data_021fbddc != 0);
        if (ok) {
            data_021f6c64 = 0;
        }
        if (data_021f6c64 < 0xc8) {
            data_021f6c64++;
        }
    }
}
