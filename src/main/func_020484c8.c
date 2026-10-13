/* func_020484c8 @ 0x020484c8, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int pad_00[13];
    int unk_34;
    int unk_38;
    int unk_3C;
    int unk_40;
} UnkStruct_020484c8;
extern UnkStruct_020484c8 data_021c79c4;
extern int func_0204f5e0(int, int, int, int, int, int);
extern void func_0204a200(int, int, int, int, int, int, int, int);

void func_020484c8(int a0, int a1)
{
    int v3c = *(volatile int *) &data_021c79c4.unk_3C;
    int v40 = *(volatile int *) &data_021c79c4.unk_40;
    int v34 = *(volatile int *) &data_021c79c4.unk_34;
    int v38 = *(volatile int *) &data_021c79c4.unk_38;
    if (func_0204f5e0(a1, v34 + 1, v38 + 1, v3c, v40, 0) != 0) {
        v3c = *(volatile int *) &data_021c79c4.unk_3C;
        v40 = *(volatile int *) &data_021c79c4.unk_40;
        v34 = *(volatile int *) &data_021c79c4.unk_34;
        v38 = *(volatile int *) &data_021c79c4.unk_38;
        func_0204a200(a0, a1, v34 + 1, v38 + 1, v3c, v40, 0x89, 0);
    }
}
