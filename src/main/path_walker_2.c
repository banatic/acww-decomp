/* path_walker_2: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0201298c @ 0x0201298c, 0x34 bytes, Thumb
 * func_02012950 @ 0x02012950, 0x3c bytes, Thumb
 */

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
} UnkStruct_0201298c;

extern void func_0204f818(int *a, int *b, int c);
extern int func_02013518(void *, int);
extern void func_02013440(void *);
extern void func_02012e58(void *, int);

int func_0201298c(UnkStruct_0201298c *s, int param)
{
    int a, b;
    a = 0;
    b = 0;
    func_0204f818(&a, &b, param);
    if (a == s->unk_0C && b == s->unk_10) {
        return 1;
    }
    return 0;
}

int func_02012950(void *arg0, int arg1)
{
    if (func_02013518(arg0, arg1) == 0) {
        func_02013440(arg0);
        *((int *) ((char *) arg0 + 0x88)) = 0;
        *((int *) ((char *) arg0 + 0x8c)) = 2;
        func_02012e58(arg0, arg1);
        return 0;
    } else {
        return 1;
    }
}
