/* func_02072e30 @ 0x02072e30, 0xa bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x32];
    unsigned char lo : 4;
    unsigned char hi : 4;
} UnkStruct_02072e30;
int func_02072e30(UnkStruct_02072e30 *p)
{
    return p->lo;
}
