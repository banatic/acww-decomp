/* func_02047730 @ 0x02047730, 0xb2 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int w[2];
} Slot;

extern void func_0209e474(void *);
extern void MI_CpuCopy8(void *, const void *, unsigned int);
extern int func_0203fc78(int, void *, void *);
extern void func_020b2f18(void);
extern void func_020b2ef8(void);
extern void func_020b2ed8(void);
extern void func_020b2a90(void);

void func_02047730(int unused, void *b)
{
    Slot slots[5];
    unsigned int flag;

    slots[0].w[0] = 0;
    slots[0].w[1] = 0;

    func_0209e474(&slots[0]);

    MI_CpuCopy8(&slots[0], &slots[1], 8);
    flag = (func_0203fc78(0x3d, &slots[1], b) == 0);
    if (flag) {
        func_020b2f18();
    }

    MI_CpuCopy8(&slots[0], &slots[2], 8);
    flag = (func_0203fc78(0x3f, &slots[2], b) == 0);
    if (flag) {
        func_020b2ef8();
    }

    MI_CpuCopy8(&slots[0], &slots[3], 8);
    flag = (func_0203fc78(0x60, &slots[3], b) == 0);
    if (flag) {
        func_020b2ed8();
    }

    MI_CpuCopy8(&slots[0], &slots[4], 8);
    flag = (func_0203fc78(0x44, &slots[4], b) == 0);
    if (flag) {
        func_020b2a90();
    }
}
