/* func_02036a5c @ 0x02036a5c, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02035624(int);

typedef struct {
    char pad_00[0x12];
    unsigned char unk_12;
} UnkStruct_02036a5c;

void func_02036a5c(UnkStruct_02036a5c *s)
{
    if (s->unk_12) {
        func_02035624(30);
        s->unk_12 = 0;
    }
}
