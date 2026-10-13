/* func_0206bf3c @ 0x0206bf3c, 0x3a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x2c];
    int unk_2C;
    unsigned int unk_30;
    int unk_34;
    unsigned char unk_38;
    unsigned char unk_39;
} UnkStruct_0206bf3c;
extern void func_020a94a4(UnkStruct_0206bf3c *a);
extern void func_020a9354(UnkStruct_0206bf3c *a, unsigned int b);
void func_0206bf3c(UnkStruct_0206bf3c *a, unsigned int b, unsigned int c, int d)
{
    if (c > b) {
        func_020a94a4(a);
        func_020a9354(a, b);
        a->unk_30 = c;
        a->unk_34 = 0;
        a->unk_39 = (unsigned char) d;
        a->unk_38 = 0;
        a->unk_2C = 2;
    }
}
