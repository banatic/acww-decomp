/* func_02034600 @ 0x02034600, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02034600 {
    unsigned char mask;
    unsigned char kind[4];
    signed char arr5[4];
    signed char arr9[4];
} UnkStruct_02034600;

extern int data_020c9050[4];

int func_02034600(UnkStruct_02034600 *s, int arg1, int arg2)
{
    int i = 0;
    signed char *a = s->arr5;
    signed char *b = s->arr9;
    unsigned char *c = s->kind;

    for (; c < (unsigned char *) s->arr5; a++, b++, i++, c++) {
        if ((s->mask >> i) & 1) {
            unsigned char v = *c;
            if (v < 3) {
                int k = 0, m = 0;
                if (a[k] == arg1 && b[m] == arg2) {
                    return data_020c9050[v];
                }
            }
        }
    }
    return 0;
}
