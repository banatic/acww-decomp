/* gatekeeper_states: 4 functions, module ov048
 * mwccarm 1.2/base -O4,s
 * func_ov048_022627dc @ 0x022627dc, 0x4 bytes, Thumb
 * func_ov048_02262784 @ 0x02262784, 0x58 bytes, Thumb
 * func_ov048_02262780 @ 0x02262780, 0x4 bytes, Thumb
 * func_ov048_0226277c @ 0x0226277c, 0x4 bytes, Thumb
 */

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_02262784;

extern int func_0201c0e0(void *a);
extern int func_0201c040(void *a, int *p1, int *p2);
extern int func_020a7278(void);
extern void func_0201c054(void *a, int b, int c, int d);
extern void func_ov048_022635f4(void *a, int b);
extern UnkStruct_02262784 *data_020ccf94;

int func_ov048_022627dc(void)
{
    return 1;
}

int func_ov048_02262784(void *a)
{
    int p1, p2;
    if (func_0201c0e0(a) == 0) {
        goto exit;
    }
    p1 = 4;
    p2 = 4;
    if (func_0201c040(a, &p1, &p2) == 0) {
        goto exit;
    }
    if (p1 != 4) {
        goto exit;
    }
    if (func_020a7278() == 0) {
        goto exit;
    }
    func_0201c054(a, 1, data_020ccf94->unk_64, 4);
    func_ov048_022635f4(a, 4);
exit:
    return 1;
}

int func_ov048_02262780(void)
{
    return 1;
}

int func_ov048_0226277c(void)
{
    return 1;
}
