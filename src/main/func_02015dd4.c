/* func_02015dd4 @ 0x02015dd4, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x40];
    int unk_40;
} UnkStruct_02015dd4;
extern int func_020683e4(int a, int b, int c, int d);
int func_02015dd4(UnkStruct_02015dd4 *p, int b, int c, int d, const void *end)
{
    return func_020683e4(p->unk_40, b, c, d);
}
