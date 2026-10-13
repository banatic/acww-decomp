/* func_ov004_02234eac @ 0x02234eac, 0x1d0 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec;
typedef struct {
    u8 id, count, pad_02[15];
} Record;
extern u8 data_ov004_022593a4, data_ov004_02255c30;
extern Record data_ov004_02247924[];
extern Vec data_ov004_022593dc;
extern void *data_021fbe94;
extern u8 *data_ov004_022594d4[];
extern u8 *func_020e9948(void *, int);
extern void *func_ov004_0223a1e8(void *), *func_ov004_0223a18c(void *), *func_ov004_02239e9c(void *),
    *func_ov004_0223a040(void *), *func_ov004_02239f68(void *), *func_ov004_02239eec(void *), *func_ov004_0223a3c4(void *);
extern int func_ov004_02234be0(void *, u8 **, int, int);
extern void func_ov004_02235374(void *, int), func_ov004_02234570(void *);
int func_ov004_02234eac(void *self)
{
    int i;
    void *heap;
    u8 **slot;
    int count;
    data_ov004_022593a4 = 0;
    data_ov004_02255c30 = 35;
    data_ov004_022593dc.x = 0x11000;
    data_ov004_022593dc.y = 0;
    data_ov004_022593dc.z = 0x15000;
    heap = data_021fbe94;
    for (i = 0; i < data_ov004_02255c30; i++) {
        switch (i) {
            case 11:
                slot = &data_ov004_022594d4[i];
                data_ov004_022594d4[i] = func_020e9948(heap, 0x214);
                if (data_ov004_022594d4[i]) {
                    func_ov004_0223a1e8(data_ov004_022594d4[i]);
                }
                break;
            case 15:
                slot = &data_ov004_022594d4[i];
                data_ov004_022594d4[i] = func_020e9948(heap, 0x210);
                if (data_ov004_022594d4[i]) {
                    func_ov004_0223a18c(data_ov004_022594d4[i]);
                }
                break;
            case 12:
                slot = &data_ov004_022594d4[i];
                data_ov004_022594d4[i] = func_020e9948(heap, 0x27c);
                if (data_ov004_022594d4[i]) {
                    func_ov004_02239e9c(data_ov004_022594d4[i]);
                }
                break;
            case 10:
                slot = &data_ov004_022594d4[i];
                data_ov004_022594d4[i] = func_020e9948(heap, 0x220);
                if (data_ov004_022594d4[i]) {
                    func_ov004_0223a040(data_ov004_022594d4[i]);
                }
                break;
            case 30:
                slot = &data_ov004_022594d4[i];
                data_ov004_022594d4[i] = func_020e9948(heap, 0x25c);
                if (data_ov004_022594d4[i]) {
                    func_ov004_02239f68(data_ov004_022594d4[i]);
                }
                break;
            case 5:
            case 6:
                slot = &data_ov004_022594d4[i];
                data_ov004_022594d4[i] = func_020e9948(heap, 0x25c);
                if (data_ov004_022594d4[i]) {
                    func_ov004_02239eec(data_ov004_022594d4[i]);
                }
                break;
            default:
                slot = &data_ov004_022594d4[i];
                data_ov004_022594d4[i] = func_020e9948(heap, 0x258);
                if (data_ov004_022594d4[i]) {
                    func_ov004_0223a3c4(data_ov004_022594d4[i]);
                }
                break;
        }
        if (!*slot) {
            return 0;
        }
        count = data_ov004_02247924[i].count;
        if (count == 3) {
            (*slot)[0x1c6] = 1;
        }
        if (!func_ov004_02234be0(self, slot, i, count)) {
            func_ov004_02235374(self, i);
            (*slot)[0x1c6] = 0;
            return 0;
        }
    }
    func_ov004_02234570(self);
    return 1;
}
