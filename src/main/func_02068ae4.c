/* func_02068ae4 @ 0x02068ae4, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_020cb8f4;

typedef struct {
    char pad_00[8];
    unsigned short arr[2];
    unsigned short cond;
    int zero;
} UnkStruct_02068ae4;

void func_02068ae4(UnkStruct_02068ae4 *p, int flag)
{
    int i = 0;
    unsigned short val = data_020cb8f4;

    do {
        p->arr[i] = val;
        i++;
    } while (i < 2);

    if (flag) {
        p->cond = val;
    }

    p->zero = 0;
}
