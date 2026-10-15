/* func_02041fe0 @ 0x02041fe0, 0x140 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0203de6c(void);
extern void func_02001bb4(int);
extern void func_02001b7c(int);
extern void func_02001da0(int);
extern void func_02001d74(int, int);
extern void func_02001d1c(int);
extern void func_02001d00(int);
extern void func_02001cc4(int, int, int, int);
extern void func_02001c7c(int, int, int, int);
extern void func_02001b44(int);
extern void func_02001b0c(int);
extern int G2_GetBG2ScrPtr(void);
extern int G2_GetBG2CharPtr(void);
extern int G2S_GetBG2ScrPtr(void);
extern int G2S_GetBG2CharPtr(void);
extern void MIi_CpuClear16(unsigned short, int, int);

struct UnkStruct_02041fe0 {
    int pad_00;
    unsigned int unk_04;
};
extern struct UnkStruct_02041fe0 data_021c75b8;

void func_02041fe0(void)
{
    volatile unsigned short arr[6];
    volatile unsigned short *reg;
    int ret;

    asm { mov r0, #0 }
    func_0203de6c();
    func_02001bb4(1);
    func_02001b7c(1);
    func_02001da0(0x1b);
    func_02001d74(0x1b, 1);
    func_02001d1c(4);
    func_02001d00(4);

    if (data_021c75b8.unk_04 == 0) {
        func_02001cc4(0, 0, 0xff, 0xc0);
        func_02001c7c(0, 0, 0xff, 0xc0);
    } else {
        func_02001cc4(0, 0, 0, 0);
        func_02001c7c(0, 0, 0, 0);
    }

    reg = (volatile unsigned short *) 0x0400000c;
    *reg &= ~3;
    *reg = (*reg & 0x43) | 0x600;

    ret = G2_GetBG2ScrPtr();
    arr[0] = 0;
    MIi_CpuClear16(arr[0], ret, 0x800);

    ret = G2_GetBG2CharPtr();
    arr[1] = 0x1111;
    MIi_CpuClear16(arr[1], ret, 0x20);

    arr[2] = 0x8000;
    MIi_CpuClear16(arr[2], 0x05000000, 4);
    func_02001b44(4);

    reg = (volatile unsigned short *) 0x0400100c;
    *reg &= ~3;
    *reg = (*reg & 0x43) | 0xe04;

    ret = G2S_GetBG2ScrPtr();
    arr[3] = 0;
    MIi_CpuClear16(arr[3], ret, 0x800);

    ret = G2S_GetBG2CharPtr();
    arr[4] = 0x1111;
    MIi_CpuClear16(arr[4], ret, 0x20);

    arr[5] = 0x8000;
    MIi_CpuClear16(arr[5], 0x05000400, 4);
    func_02001b0c(4);
}
