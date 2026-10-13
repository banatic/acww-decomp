/* func_02072e3c @ 0x02072e3c, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned short data[10];
} Block;
typedef struct {
    unsigned short head[15];
    Block block;
} Record;

void func_02072e3c(Record *dst, Block *src)
{
    dst->block = *src;
}
