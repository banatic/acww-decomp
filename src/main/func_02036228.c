/* func_02036228 @ 0x02036228, 0x3a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02036228 {
    unsigned char pad_00[12];
    int state;
} UnkStruct_02036228;

extern void func_02036558(UnkStruct_02036228 *p, int a, int b, int c);

void func_02036228(int unused, UnkStruct_02036228 *p)
{
    int v = p->state;
    if (v == 13) {
        func_02036558(p, 0x28, 0xf, 1);
        p->state = 14;
    } else if (v == 14) {
    } else if (v == 15) {
        func_02036558(p, 0x7f, 0xf, 1);
        p->state = 0;
    }
}
