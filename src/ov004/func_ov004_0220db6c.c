/* func_ov004_0220db6c @ 0x0220db6c, 0x22 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int count;
    struct {
        int a;
        int b;
    } e[4];
} UnkStruct_0220db6c;
int func_ov004_0220db6c(UnkStruct_0220db6c *s, int a, int b)
{
    if (s->count < 4) {
        s->e[s->count].a = a;
        s->e[s->count].b = b;
        s->count = s->count + 1;
        return 1;
    }
    return 0;
}
