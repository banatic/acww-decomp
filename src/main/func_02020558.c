/* func_02020558 @ 0x02020558, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206e94c(void);
extern int func_0208150c(int value);
extern void func_0207a4c0(void *base, void *value);

typedef struct StructB_02020558 {
    unsigned char pad_00[0x830];
    int unk_830;
} StructB_02020558;

typedef struct StructA_02020558 {
    unsigned char pad_00[0x100];
    StructB_02020558 *unk_100;
} StructA_02020558;

extern unsigned char data_021e5a2c[];

void func_02020558(StructA_02020558 *arg, int event)
{
    StructB_02020558 *p;
    int v;
    int res;

    func_0206e94c();
    p = arg->unk_100;
    v = p->unk_830;
    res = func_0208150c(v);
    func_0207a4c0((void *) data_021e5a2c, (void *) res);
}
