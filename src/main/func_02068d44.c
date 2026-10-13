/* func_02068d44 @ 0x02068d44, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x74];
    int unk_74;
    int unk_78;
} UnkStruct_02068d44;
extern void func_02001e54(int a, int b);
extern void func_02001cc4(int a, int b, int c, int d);
void func_02068d44(UnkStruct_02068d44 *s, int a, int b)
{
    int val, val2;
    s->unk_74 = a;
    s->unk_78 = b;
    func_02001e54(a, b);
    val = 255 - a;
    val2 = -a;
    if (val2 < 0) {
        val2 = 0;
    }
    if (val > 255) {
        val = 255;
    }
    func_02001cc4(val2, 60, val, 192);
}
