/* func_0201ffa0 @ 0x0201ffa0, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208150c(int);
extern int func_020036e8(int);
extern void func_0202da38(unsigned char *, unsigned char *, unsigned char *, int, int, int, int, int, int);
extern void func_020819e0(int);

typedef struct {
    int first;
    unsigned char second;
} Data020c8ce8_t;

extern Data020c8ce8_t data_020c8ce8;

void func_0201ffa0(unsigned char *param0, unsigned char *param1)
{
    int val0, val1, val4;
    unsigned char *p;
    int v;

    p = *(unsigned char **) (param0 + 0x100);
    v = *(int *) (p + 0x830);
    val0 = func_020036e8(func_0208150c(v));

    val1 = data_020c8ce8.first;
    val4 = data_020c8ce8.second;

    func_0202da38(param0, param0 + 0x104, param0 + 0x122, 30, val0, val1, 1, 2, val4);

    *(unsigned char **) param1 = param0 + 0x104;
    *(unsigned char *) (param1 + 4) = *(unsigned char *) (param0 + 0x122);

    v = *(int *) (param0 + 0x12c);
    if (v != 0) {
        func_020819e0(v);
    }
}
