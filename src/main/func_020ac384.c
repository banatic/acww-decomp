/* func_020ac384 @ 0x020ac384, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[8];
    unsigned short arr[5];
    unsigned char flag;
} UnkStruct_020ac384;

void func_020ac384(UnkStruct_020ac384 *s)
{
    int i;
    for (i = 0; i < 5; i++) {
        s->arr[i] = 12;
    }
    s->flag = 1;
}
