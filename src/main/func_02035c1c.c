/* func_02035c1c @ 0x02035c1c, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[8];
    unsigned char unk_08;
    unsigned char pad_09[2];
    unsigned char unk_0B;
} UnkStruct_02035c1c;

void func_02035c1c(UnkStruct_02035c1c *s, int a, int b)
{
    if (s->unk_0B == 2) {
        s->unk_0B = 3;
        return;
    }
    {
        int flag0 = (a == 0);
        int flag1 = (a == 1);
        int flag2 = (a == 2 && b == 6);
        if (flag0 || flag1 || !flag2) {
            s->unk_08 = 1;
        }
    }
}
