/* func_02021ba8 @ 0x02021ba8, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02021ea8(int a, int b, int c, void (*d)(void));
extern int func_020814f4(int a);
extern int func_02065f7c(int a);
extern void func_020642fc(void *p);
extern void func_020642bc(void *p, int a);
extern void func_02015e70(void *a, void *p, int b);
extern void func_020642f8(void *p);
extern void func_02021c08(void);

typedef struct UnkStruct_02021ba8 {
    char pad_00[0x830];
    int unk_830;
} UnkStruct_02021ba8;

typedef struct UnkStruct_02021ba8_2 {
    char pad_00[0x100];
    UnkStruct_02021ba8 *unk_100;
} UnkStruct_02021ba8_2;

int func_02021ba8(UnkStruct_02021ba8_2 *a, int b, int c)
{
    int ret = func_02021ea8(a->unk_100->unk_830, b, c, func_02021c08);
    if (ret) {
        int r6 = func_02065f7c(func_020814f4(a->unk_100->unk_830));
        int local[4];
        func_020642fc(local);
        func_020642bc(local, r6);
        func_02015e70(a, local, 9);
        func_020642f8(local);
    }
    return ret;
}
