/* func_02025e70 @ 0x02025e70, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern struct Data1 {
    int unk_00;
    unsigned char unk_04;
} data_020c8d48;
extern struct Pair {
    int a;
    int b;
} data_020d9370;
extern int func_0208150c(int);
extern int func_020036e8(int);
extern int func_0202da38(void *, void *, void *, int, int base, int offset, int scale, int multiplier, int selected);
extern void func_0202db48(void *, struct Pair);

typedef struct {
    void *ptr;
    unsigned char byte;
} Param1;

void func_02025e70(void *param0, Param1 *param1)
{
    struct {
        int a;
        int b;
        int c;
        int d;
        int e;
    } local;

    local.a = func_020036e8(func_0208150c(*(int *) ((char *) (*(void **) ((char *) param0 + 0x100)) + 0x830)));
    local.b = data_020c8d48.unk_00;
    local.c = data_020c8d48.unk_04;
    local.d = 0;
    local.e = 0;

    func_0202da38(param0, (char *) param0 + 0x104, (char *) param0 + 0x122, 30, local.a, local.b, local.c, local.d, local.e);
    param1->ptr = (char *) param0 + 0x104;
    param1->byte = *(unsigned char *) ((char *) param0 + 0x122);

    func_0202db48(param0, data_020d9370);
}
