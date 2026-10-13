/* func_02060a34 @ 0x02060a34, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02060a34 UnkStruct_02060a34;
extern UnkStruct_02060a34 data_021ed268;
extern int func_02060a70(UnkStruct_02060a34 *p, int i);
static __inline int idxOf(unsigned int x)
{
    if (x >= 0x1323 && x <= 0x1368) {
        return (int) (x - 0x1323);
    }
    return -1;
}
int func_02060a34(unsigned int x)
{
    if (x >= 0x1323 && x <= 0x1368) {
        return func_02060a70(&data_021ed268, idxOf(x));
    }
    return 0;
}
