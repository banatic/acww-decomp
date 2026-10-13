/* func_ov003_02221464 @ 0x02221464, 0x24 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int pad_00;
    int flag;
    char rest[0x9C];
} Entry;

Entry *func_ov003_02221464(Entry *base, int idx)
{
    Entry *result = 0;
    int i;
    Entry *p;

    p = base + idx * 4;
    for (i = 0; i < 4; i++) {
        if (p->flag == 0) {
            result = p;
            break;
        }
        p++;
    }
    return result;
}
