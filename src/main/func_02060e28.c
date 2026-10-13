/* func_02060e28 @ 0x02060e28, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x15a0];
    unsigned int lo : 3;
    unsigned int bits : 3;
    unsigned int hi : 26;
} UnkStruct_02060e28;
extern int func_02060e78(UnkStruct_02060e28 *p);
int func_02060e28(UnkStruct_02060e28 *p)
{
    if (p->bits == (unsigned int) func_02060e78(p)) {
        if (func_02060e78(p) < 6) {
            p->bits = (unsigned char) (func_02060e78(p) + 1);
            return 1;
        }
    }
    return 0;
}
