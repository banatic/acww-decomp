/* func_ov009_02264884 @ 0x02264884, 0x20 bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x138];
    unsigned int idx;
} Param;

extern char data_ov009_02265cb4[][0x50];

char *func_ov009_02264884(Param *p)
{
    if (p->idx < 0x22) {
        return data_ov009_02265cb4[p->idx];
    } else {
        return 0;
    }
}
