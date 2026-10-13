/* func_ov003_0221ffcc @ 0x0221ffcc, 0x20 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a[4];
    int b[4];
    int x;
    int y;
} UnkStruct_0221ffcc;

void func_ov003_0221ffcc(volatile UnkStruct_0221ffcc *p)
{
    unsigned int i;
    int v;

    i = 0;
    v = i;
    do {
        p->a[i] = v;
        p->b[i] = v;
        i++;
    } while (i < 4);
    p->y = v;
    p->x = p->y;
}
