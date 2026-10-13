/* func_020e9314 @ 0x020e9314, 0x178 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

typedef struct {
    u16 x;
    u16 y;
    u16 touch;
    u16 validity;
} TPData;
extern volatile TPData data_021fbdf0[9];
extern TPData data_021fbde8;
extern u8 data_021fbdd8;
extern u8 data_021fbddc;
extern u16 data_021fbde0;
extern u16 data_021fbde4;
extern int TP_GetLatestIndexInAuto(void);
extern void TP_GetCalibratedPoint(TPData *disp, const TPData *raw);
void func_020e9314(void)
{
    int i;
    TPData sample[4];
    int hasTouch;
    int index;
    TPData *ptr;
    int valid;
    index = TP_GetLatestIndexInAuto();
    hasTouch = 0;
    i = 0;
    do {
        int idx = (index - 4) + i;
        if (idx < 0) {
            idx += 9;
        }
        if (data_021fbdf0[idx].touch != 0) {
            hasTouch = 1;
        }
        valid = data_021fbdf0[idx].validity;
        if (valid != 0) {
            sample[i].touch = 0;
        } else {
            sample[i].x = data_021fbdf0[idx].x;
            sample[i].y = data_021fbdf0[idx].y;
            sample[i].touch = data_021fbdf0[idx].touch;
            sample[i].validity = data_021fbdf0[idx].validity;
        }
        i++;
    } while (i < 4);

    if (((sample[3].touch != 0) && (sample[2].touch != 0)) && ((&sample[1])->touch != 0)) {
        TP_GetCalibratedPoint(&data_021fbde8, &sample[2]);
    } else if (((sample[0].touch != 0) && (sample[1].touch != 0)) && (sample[2].touch != 0)) {
        TP_GetCalibratedPoint(&data_021fbde8, &sample[1]);
    } else if (hasTouch == 0) {
        data_021fbde8.touch = 0;
        data_021fbde8.x = 0xff;
        data_021fbde8.y = 0xff;
        data_021fbde8.validity = 0;
    }
    data_021fbddc = data_021fbde8.touch ^ data_021fbdd8;
    data_021fbdd8 = data_021fbde8.touch;
    data_021fbde0 = data_021fbde8.x;
    data_021fbde4 = data_021fbde8.y;
}
