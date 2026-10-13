/* func_020ec040 @ 0x020ec040, 0x108 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

extern u32 data_021fbf98;
extern u32 data_021fbf18;
extern u32 data_0213e6b8;
extern u64 OS_GetTick(void);
extern void func_020ed9f4(void);
extern int OS_ReadMessage(void *queue, u32 *msg, u32 flags);

int func_020ec040(u32 param)
{
    u32 msg;
    u64 q;
    unsigned int flag;

    if (param != 0) {
        if (OS_ReadMessage(&data_021fbf98, &msg, 0)) {
            if (data_021fbf18 != 0) {
                q = OS_GetTick();
                q = (q << 6) / 0x82eaULL;
                flag = (q - (u64) data_021fbf18) > (u64) data_0213e6b8;
                if (flag != 0) {
                    data_021fbf18 = 0;
                    func_020ed9f4();
                }
            } else {
                q = OS_GetTick();
                q = (q << 6) / 0x82eaULL;
                data_021fbf18 = (u32) q;
            }
        } else {
            data_021fbf18 = 0;
            return 1;
        }
    } else {
        data_021fbf18 = 0;
    }
    return 0;
}
