/* func_ov127_02299878 @ 0x02299878, 0x18 bytes, Thumb, module ov127
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x2830];
    unsigned short flags;
} Struct_ov127_02299878;

int func_ov127_02299878(Struct_ov127_02299878 *s, unsigned int mask)
{
    if ((s->flags & mask) != 0) {
        return 1;
    } else {
        return 0;
    }
}
