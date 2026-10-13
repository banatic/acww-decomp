/* func_020adf8c @ 0x020adf8c, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020aff84(int, void *, void *, int);

struct UnkStruct_020adf8c {
    char pad_00[0x10];
    char unk_10;
};

int func_020adf8c(struct UnkStruct_020adf8c *a, int b)
{
    return func_020aff84(b, a, &a->unk_10, 3);
}
