/* network_2: 2 functions, module autoload_2
 * mwccarm 1.2/base -O4,p
 * func_020eaf48 @ 0x020eaf48, 0xf8 bytes, ARM
 * func_020eae80 @ 0x020eae80, 0xc8 bytes, ARM
 */

#include "types.h"

typedef struct {
    unsigned char data[12];
} SomeObj;

extern int DWC_CanChangeFriendList(void);
extern unsigned short data_021fbefc;
extern int data_0213e6c4;
extern SomeObj *data_021fbf3c;
extern void MI_CpuCopy8(const void *, void *, unsigned int);
extern void MI_CpuFill8(void *, int, unsigned int);
extern int func_ov065_02277edc(int, void (*)(void *, int, void *), int, void (*)(int, int, void *, void *), int,
                               void (*)(int, int, void *), int);
extern void func_020ed440(int index, int reason, void *user_data);
extern void func_020ed540(void *result, int changed, void *user_data);
extern void func_020ed4cc(int index, int status, void *profile, void *user_data);
extern void func_ov065_022797a4(void *param);

int func_020eaf48(int idx, void *data)
{
    int result;
    int offset;

    if (DWC_CanChangeFriendList() == 0) {
        goto fail;
    }
    if (data_021fbefc < 5) {
        goto fail;
    }
    if (data_0213e6c4 == 0) {
        goto success;
    }

fail:
    return 0;

success:
    MI_CpuCopy8(data, &data_021fbf3c[idx], 12);

    offset = idx * 0x23;
    MI_CpuFill8((unsigned char *) data_021fbf3c + 0x180 + offset, 0, 0x23);
    ((unsigned char *) data_021fbf3c + offset)[0x1a0] = 0;
    data_0213e6c4 = 1;

    result = func_ov065_02277edc(0, func_020ed540, 0, func_020ed4cc, 0, func_020ed440, 0);
    if (result == 0) {
        data_0213e6c4 = 0;
    }
    return result;
}

int func_020eae80(int idx)
{
    void *base;

    if (!DWC_CanChangeFriendList() || data_021fbefc < 5 || (*(unsigned int *) &data_0213e6c4) != 0) {
        return 0;
    }

    base = (*(void * *) &data_021fbf3c);
    func_ov065_022797a4((u8 *) base + idx * 0xc);

    MI_CpuFill8((u8 *) (*(void * *) &data_021fbf3c) + idx * 0xc, 0, 0xc);
    MI_CpuFill8((u8 *) (*(void * *) &data_021fbf3c) + 0x180 + idx * 0x23, 0, 0x23);
    *((u8 *) (*(void * *) &data_021fbf3c) + idx * 0x23 + 0x1a0) = 0;

    return 1;
}
