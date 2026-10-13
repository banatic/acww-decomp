/* func_020909f8 @ 0x020909f8, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a;
    int pad_04[5];
} UnkStruct_020909f8;

typedef struct {
    char flag;
    UnkStruct_020909f8 arr[32];
} UnkStruct_020909f8_2;

void func_020909f8(UnkStruct_020909f8_2 *s)
{
    UnkStruct_020909f8 *p;
    int i;

    p = &s->arr[0];
    do {
        p->a = -1;
        p++;
    } while (p != &s->arr[32]);

    s->flag = 0;

    for (i = 0; i < 32; i++) {
        s->arr[i].a = -1;
    }
}
