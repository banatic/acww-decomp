/* func_020ed950 @ 0x020ed950, 0xa4 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

typedef struct {
    u32 unk_00;
    u32 unk_04;
    u32 unk_08;
    void (*fn)(void *arg);
} Entry;

extern u32 data_021fbf98;
extern Entry data_021fc120[];

extern int func_g1(u32 *q, u32 *out, int flags);
extern int OS_ReceiveMessage(u32 *q, u32 *out, int flags);
extern int OS_ReadMessage(u32 *q, u32 *out, int flags);
extern void func_020edb14(void);
extern int func_020ed9f4(int r);

void func_020ed950(void *arg)
{
    u32 idx;
    Entry *e;
    int r;

    if (OS_ReceiveMessage(&data_021fbf98, &idx, 0) == 0) {
        return;
    }
    e = &data_021fc120[idx];
    if (e->fn != 0) {
        e->fn(arg);
    }
    e->unk_00 = 0;
    goto test;
loop:
    func_020edb14();
test:
    r = OS_ReadMessage(&data_021fbf98, &idx, 0);
    if (r == 0) {
        return;
    }
    if (func_020ed9f4(r) == 0) {
        goto loop;
    }
}
