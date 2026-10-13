/* func_02002354 @ 0x02002354, 0xb4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void GX_SetGraphicsMode(int, int, int);
extern void GXS_SetGraphicsMode(int);
extern unsigned char data_0213fe74[];

#define REG_DISPCNT (*(volatile unsigned int *) 0x04000000)
#define REG_DISPCNT_SUB (*(volatile unsigned int *) 0x04001000)
#define REG_WINOUT (*(volatile unsigned short *) 0x0400004a)
#define REG_WINOUT_SUB (*(volatile unsigned short *) 0x0400104a)

void func_02002354(void)
{
    unsigned int v;
    unsigned short w;

    GX_SetGraphicsMode(1, data_0213fe74[0x16], 1);
    GXS_SetGraphicsMode(data_0213fe74[0x17]);

    v = REG_DISPCNT;
    v = (v & ~0x1f00) | (data_0213fe74[0x14] << 8);
    REG_DISPCNT = v;

    v = REG_DISPCNT_SUB;
    v = (v & ~0x1f00) | (data_0213fe74[0x15] << 8);
    REG_DISPCNT_SUB = v;

    v = REG_DISPCNT;
    v = (v & ~0xe000) | (data_0213fe74[0x18] << 13);
    REG_DISPCNT = v;

    v = REG_DISPCNT_SUB;
    v = (v & ~0xe000) | (data_0213fe74[0x19] << 13);
    REG_DISPCNT_SUB = v;

    w = REG_WINOUT;
    w = (w & ~0x3f) | data_0213fe74[0x1a] | 0x20;
    REG_WINOUT = w;

    w = REG_WINOUT_SUB;
    w = (w & ~0x3f) | data_0213fe74[0x1b] | 0x20;
    REG_WINOUT_SUB = w;

    w = REG_WINOUT;
    w = (w & ~0x3f00) | (data_0213fe74[0x1c] << 8);
    REG_WINOUT = w;

    w = REG_WINOUT_SUB;
    w = (w & ~0x3f00) | (data_0213fe74[0x1d] << 8);
    REG_WINOUT_SUB = w;
}
