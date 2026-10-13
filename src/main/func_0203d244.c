/* func_0203d244 @ 0x0203d244, 0xc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00;
    unsigned char flag;
} UnkStruct_0203d244;

void func_0203d244(UnkStruct_0203d244 *p)
{
    p->flag = (p->flag & ~1) | 1;
}
