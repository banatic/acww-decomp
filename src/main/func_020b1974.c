/* func_020b1974 @ 0x020b1974, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x4a0];
    unsigned short flag;
} Func020b1974Struct;

int func_020b1974(Func020b1974Struct *s, int bit)
{
    int value = s->flag & (1 << bit);
    if (value) {
        return 1;
    } else {
        return 0;
    }
}
