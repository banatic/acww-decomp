/* func_0202da08 @ 0x0202da08, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0201ce50(int);

typedef struct {
    char pad_00[0x100];
    int member;
} UnkStruct_0202da08;

int func_0202da08(UnkStruct_0202da08 *base, int mode)
{
    int v;

    switch (mode) {
        case 0:
            return base->member;
        case 1:
            v = base->member;
            if (v != 0) {
                return func_0201ce50(v);
            }
            // fall through
        default:
            return 0;
    }
}
