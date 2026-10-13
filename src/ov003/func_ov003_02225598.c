/* func_ov003_02225598 @ 0x02225598, 0x70 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int w[12];
} UnkStruct_02225598;

extern int func_02049ec4(void *b);
extern int func_02049d78(void *b);
extern void func_ov003_022251a4(char *a, char *p, UnkStruct_02225598 m);

char *func_ov003_02225598(char *a, void *b, UnkStruct_02225598 m)
{
    int i;
    int j;
    char *p;
    i = func_02049ec4(b);
    j = func_02049d78(b);
    p = a + 0x1590 + i * 0x618 + j * 0x9c;
    func_ov003_022251a4(a, p, m);
    return p;
}
