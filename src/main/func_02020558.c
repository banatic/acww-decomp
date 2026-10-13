/* func_02020558 @ 0x02020558, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206e94c(void *arg);
extern int func_0208150c(int value);
extern int func_0207a4c0(void *base, int value);

typedef struct StructB_02020558 {
    unsigned char pad_00[0x830];
    int unk_830;
} StructB_02020558;

typedef struct StructA_02020558 {
    unsigned char pad_00[0x100];
    StructB_02020558 *unk_100;
} StructA_02020558;

extern unsigned char data_021e5a2c[];

int func_02020558(StructA_02020558 *arg)
{
    StructB_02020558 *p;
    int v;
    int res;

    func_0206e94c(arg);
    p = arg->unk_100;
    v = p->unk_830;
    res = func_0208150c(v);
    return func_0207a4c0((void *) data_021e5a2c, res);
}
