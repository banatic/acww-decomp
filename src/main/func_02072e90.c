/* func_02072e90 @ 0x02072e90, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned short data[10];
} Block;
typedef struct {
    unsigned short head[15];
    Block block;
} Record;

void func_02072e90(Record *src, Block *dst)
{
    *dst = src->block;
}
