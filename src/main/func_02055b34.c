/* func_02055b34 @ 0x02055b34, 0xc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a;
    int b;
    int c;
    int d;
    char e;
    char unk_11;
} UnkStruct_02055b34;

void func_02055b34(UnkStruct_02055b34 *s, int v1, int v2, int v3)
{
    s->b = v1;
    s->c = v2;
    s->d = v3;
    s->unk_11 = 1;
}
