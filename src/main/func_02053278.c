/* func_02053278 @ 0x02053278, 0x56 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char lo : 4;
    unsigned char hi : 4;
} UnkStruct_02053278;
typedef struct {
    UnkStruct_02053278 e[4];
    unsigned char mask[1];
    unsigned char val[2];
} UnkStruct_02053278_2;

int func_02053278(UnkStruct_02053278_2 *t, int a, int b)
{
    unsigned int i;

    for (i = 0; i < 4; i++) {
        if ((((int) t->mask[i >> 3] >> (i & 7)) & 1) != 0) {
            if (a == t->e[i].lo && b == t->e[i].hi) {
                return ((int) t->val[i >> 1] >> ((i & 1) * 4)) & 0xf;
            }
        }
    }
    return -1;
}
