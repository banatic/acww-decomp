/* func_02023980 @ 0x02023980, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208150c(int);
extern int func_020036e8(int);
struct SomeOuter;
struct UnkStruct_02023980;
struct UnkStruct_02023980_2;
struct GlobalData;
struct Global2;
extern void func_0202da38(struct SomeOuter *, char *, unsigned char *, int, int, int, int, int, int);
extern struct GlobalData data_020c8bf8;
extern struct Global2 data_020d94d0;
struct GlobalData {
    int unk_00;
    unsigned char unk_04;
};
struct Global2 {
    int unk_00;
    int word1;
};
struct UnkStruct_02023980_2 {
    char pad_00[0x830];
    unsigned int unk_830;
};
struct SomeOuter {
    char pad_00[0xc8];
    struct Global2 unk_C8;
    char pad_D0[0x100 - 0xd0];
    struct UnkStruct_02023980_2 *inner;
    char unk_104[0x1e];
    unsigned char unk_122;
    char pad_123[0x15a - 0x123];
    unsigned short unk_15A;
};
struct UnkStruct_02023980 {
    char *ptr;
    unsigned char unk_04;
};
void func_02023980(struct SomeOuter *a, struct UnkStruct_02023980 *b)
{
    int val;
    int val2;
    int val3;
    int val4;
    int val5;
    val = func_020036e8(func_0208150c(a->inner->unk_830));
    val2 = data_020c8bf8.unk_00;
    val3 = (int) data_020c8bf8.unk_04;
    val4 = 0;
    val5 = 0;
    func_0202da38(a, a->unk_104, &a->unk_122, 0x1e, val, val2, val3, val4, val5);
    b->ptr = a->unk_104;
    b->unk_04 = a->unk_122;
    a->unk_15A = 0x5f;
    a->unk_C8 = data_020d94d0;
}
