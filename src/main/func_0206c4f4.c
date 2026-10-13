/* func_0206c4f4 @ 0x0206c4f4, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0206c4f4 {
    char pad_00[0x2c];
    int unk_2C;
} UnkStruct_0206c4f4;

extern int func_0206d420(UnkStruct_0206c4f4 *p, int a, int b);

int func_0206c4f4(UnkStruct_0206c4f4 *p)
{
    int sum1 = p->unk_2C + 0x14b8;
    int sum2 = sum1 + 0x33c;
    return func_0206d420(p, sum2, sum1);
}
