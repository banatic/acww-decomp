/* func_020eaf48 @ 0x020eaf48, 0xf8 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern int DWC_CanChangeFriendList(int, void *);
extern unsigned short data_021fbefc;
extern int data_0213e6c4;
typedef struct {
    unsigned char data[12];
} SomeObj;
extern SomeObj *data_021fbf3c;
extern void MI_CpuCopy8(const void *, void *, unsigned int);
extern void MI_CpuFill8(void *, int, unsigned int);
extern int func_ov065_02277edc(int, void (*)(void), int, void (*)(void), int, void (*)(void), int);
extern void func_020ed440(void);
extern void func_020ed540(void);
extern void func_020ed4cc(void);

int func_020eaf48(int idx, void *data)
{
    int result;
    int offset;

    if (DWC_CanChangeFriendList(idx, data) == 0) {
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