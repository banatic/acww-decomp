/* func_020beca4 @ 0x020beca4, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020becbc(int, int);

struct UnkStruct_020d2bac {
    char pad_00[13];
    signed char unk_0D;
    char pad_0E[2];
};

extern struct UnkStruct_020d2bac data_020d2bac[];

void func_020beca4(int a, int b)
{
    register int offset = 13;
    func_020becbc(a, *(signed char *) ((char *) &data_020d2bac[b] + offset));
}
