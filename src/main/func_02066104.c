/* func_02066104 @ 0x02066104, 0x94 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02094fd4(void *ptr);
extern void func_02003618(int a, void *ptr);
extern void func_0203d7c4(int a, void *ptr);
extern void func_02094fbc(void *ptr);
extern void func_0203d73c(void *ptr);
extern void func_0203d834(void *p1, void *p2, void *p3, int *out, int a, int b, int c, int d, int e);
extern void func_02066198(int a, void *p1, void *p2, void *p3, int b, int c, int d, int e);

extern char data_021cd8c4[];
extern char data_021cd9b0[];
extern char data_021cd8ec[];

struct UnkStruct_02066104 {
    char data[0x20];
};
struct UnkStruct_02066104_2 {
    char data[0x24];
};

void func_02066104(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10)
{
    int local14;
    struct UnkStruct_02066104 local18;
    struct UnkStruct_02066104_2 local38;

    if (a10 != 0xb) {
        func_02094fd4(&local18);
        func_02003618(a8, &local18);
        func_0203d7c4(a10, &local18);
        func_02094fbc(&local18);
    }

    func_02094fd4(&local38);
    func_02003618(a9, &local38);
    func_0203d73c(&local38);
    func_02094fbc(&local38);

    func_0203d834(data_021cd8c4, data_021cd9b0, data_021cd8ec, &local14, a2, a3, a4, a5, a6);

    func_02066198(a1, data_021cd8c4, data_021cd9b0, data_021cd8ec, local14, a7, a8, a9);

    return;
}
