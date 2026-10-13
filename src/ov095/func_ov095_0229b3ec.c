/* func_ov095_0229b3ec @ 0x0229b3ec, 0x12 bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    short arr[6];
    int unk_0C;
} UnkStruct_0229b3ec;

void func_ov095_0229b3ec(UnkStruct_0229b3ec *p)
{
    int i;
    i = 0;
    do {
        p->arr[i] = 0;
        i++;
    } while (i < 6);
    p->unk_0C = 0;
}
