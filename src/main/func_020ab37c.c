/* func_020ab37c @ 0x020ab37c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00;
    int unk_04;
    int array[5];
    int unk_1C;
    int unk_20;
    int unk_24;
    int unk_28;
    int unk_2C;
} UnkStruct_020ab37c;

void func_020ab37c(UnkStruct_020ab37c *s, int val)
{
    unsigned int i;
    int zero = 0;
    s->unk_00 = zero;
    s->unk_04 = val;
    s->unk_1C = zero;
    s->unk_20 = zero;
    s->unk_24 = zero;
    s->unk_28 = zero;
    s->unk_2C = zero;
    for (i = 0; i < 5; i++) {
        s->array[i] = zero;
    }
}
