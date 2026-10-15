/* func_0201abac @ 0x0201abac, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x28];
    short unk_28;
} UnkStruct_0201abac;

int func_0201abac(UnkStruct_0201abac *p, int a)
{
    int abs_a = a < 0 ? -a : a;
    short limit = p->unk_28;
    if (abs_a > limit) {
        if (a > 0) {
            a = limit;
        } else {
            a = (short) -limit;
        }
    }
    return a;
}
