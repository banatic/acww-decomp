/* func_02055bac @ 0x02055bac, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xc];
    unsigned int c;
} UnkStruct_02055bac;

unsigned int func_02055bac(UnkStruct_02055bac *s, unsigned int p1, unsigned int p2)
{
    unsigned int t = (s->c & 0xffff) << 3;
    t += ((p1 & 0xffff0000) >> 16) << 3;
    return ((p2 >> 3) << 16) | ((t >> 3) & 0xffff);
}
