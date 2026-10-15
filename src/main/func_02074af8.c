/* func_02074af8 @ 0x02074af8, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02074af8 {
    unsigned char pad_00[0x74];
    unsigned char unk_74;
} UnkStruct_02074af8;

extern UnkStruct_02074af8 *data_020ccf94;

extern unsigned int func_02073044(void);
extern int func_02077afc(int size, int type);
extern void func_02077ae8(int r);
extern void func_020ece54(int code, int a, int b, long long size, int n, int (*f1)(int, int), void (*f2)(int));

void func_02074af8(void)
{
    data_020ccf94->unk_74 = 1;
    func_02073044();
    func_020ece54(0x41444d4b, 0x00c0001c, 1, 0x004fe752, 2, func_02077afc, func_02077ae8);
}
