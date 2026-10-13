/* func_02036264 @ 0x02036264, 0x3a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[12];
    int state;
} UnkStruct_02036264;

extern void func_02036558(UnkStruct_02036264 *s, int a, int b, int c);

void func_02036264(int unused, UnkStruct_02036264 *s)
{
    int st;
    st = s->state;
    if (st == 10) {
        func_02036558(s, 0x28, 0xf, 1);
        s->state = 11;
    } else if (st != 11) {
        if (st == 12) {
            func_02036558(s, 0x7f, 0xf, 1);
            s->state = 0;
        }
    }
}
