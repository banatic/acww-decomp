/* func_0207f6dc @ 0x0207f6dc, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x078c];
    unsigned short arr[10];
} UnkStruct_0207f6dc;

int func_0207f6dc(UnkStruct_0207f6dc *base)
{
    unsigned short *p;
    int i;
    int count;

    p = base->arr;
    count = 0;
    for (i = 0; i < 10; i++) {
        if (*p != 0xfff1) {
            count++;
        }
        p++;
    }
    return count;
}
