/* func_020aa360 @ 0x020aa360, 0x92 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209d368(int a, int b);
extern void func_020ac39c(void *a, int b, int c);
extern void func_020ab2e0(void *a);
extern void func_020ac3e0(void *a);
extern void func_020aa678(void *a);

typedef struct {
    char pad_00[0x0c];
    int unk_0C;        // offset 0x0c
    char pad_10[0x74]; // offset 0x10 to 0x84
    int unk_84;        // offset 0x84
    char pad_88[0x2c]; // offset 0x88 to 0xb4
    int unk_B4;        // offset 0xb4
    int unk_B8;        // offset 0xb8
    int unk_BC;        // offset 0xbc
    char unk_C0;       // offset 0xc0
} UnkStruct_020aa360;

void func_020aa360(UnkStruct_020aa360 *r5)
{
    int flag;

    r5->unk_B4 += func_0209d368(0x65, 3) + 0x11;
    r5->unk_B8 += func_0209d368(0x65, 4) - 0x11;

    r5->unk_BC--;
    flag = (r5->unk_BC > 0) ? 0 : 1;

    func_020ac39c(&r5->unk_0C, r5->unk_B4, r5->unk_B8);
    r5->unk_C0 = 0;

    if (flag) {
        func_020ab2e0(&r5->unk_84);
        func_020ac3e0(&r5->unk_0C);
        func_020aa678(r5);
    }
}
