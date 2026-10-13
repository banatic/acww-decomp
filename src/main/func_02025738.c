/* func_02025738 @ 0x02025738, 0x88 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0202d9c4(char *, char *);
extern int func_0209bc40(void);
extern int func_0208150c(int);
extern int func_020036e8(int);
extern void func_0202da38(char *, char *, char *, int, int, int, int, int, int);

struct Table {
    int word;
    unsigned char unk_04;
};

extern struct Table data_020c8ce0;
extern struct Table data_020c8ad8;

struct Pair {
    int a;
    int b;
};

extern struct Pair data_020d8f90;

void func_02025738(char *a, char *b)
{
    struct Table *t;
    void *p;
    int val;
    int temp;
    int v;

    t = &data_020c8ce0;
    func_0202d9c4(a, b);
    if (func_0209bc40() == 1) {
        t = &data_020c8ad8;
    }

    p = *(void **) (a + 0x100);
    val = *(int *) ((char *) p + 0x830);
    temp = func_0208150c(val);
    v = func_020036e8(temp);

    func_0202da38(a, a + 0x104, a + 0x122, 0x1e, v, t->word, t->unk_04, 0, 0);

    *(char **) b = a + 0x104;
    *(unsigned char *) (b + 4) = *(unsigned char *) (a + 0x122);

    *(struct Pair *) (a + 0xc8) = data_020d8f90;
}
