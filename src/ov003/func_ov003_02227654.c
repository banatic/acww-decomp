/* func_ov003_02227654 @ 0x02227654, 0x2c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x24c];
} UnkStruct_02227654;
extern UnkStruct_02227654 data_ov003_0225f76c[];
UnkStruct_02227654 *func_ov003_02227654(int i)
{
    UnkStruct_02227654 *e;
    int s;
    if (i < 0 || i >= 6) {
        return 0;
    }
    e = &data_ov003_0225f76c[i];
    s = *(int *) ((char *) e + 0x80);
    if ((unsigned int) (s - 3) > 1) {
        e = 0;
    }
    return e;
}
