/* func_0209e268 @ 0x0209e268, 0x32 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0209e268 {
    unsigned char pad_00[2];
    unsigned char unk_02;
};

extern void func_0209e29c(struct UnkStruct_0209e268 *ptr, int n);

void func_0209e268(struct UnkStruct_0209e268 *ptr, int add)
{
    int v = ptr->unk_02 + add;
    if (v >= 24) {
        func_0209e29c(ptr, v / 24);
        v = v % 24;
    }
    ptr->unk_02 = v;
}
