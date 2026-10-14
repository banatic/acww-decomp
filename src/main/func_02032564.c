/* func_02032564 @ 0x02032564, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_ctor(void *, int, int, void (*)(), void (*)());
extern void func_020325b8(void *);
extern char data_020da1b4;
extern void func_020012dc();
extern void func_020012e8();
extern void func_0202f2f0();
extern void func_02032550();

typedef struct {
    void *unk_00;
    char pad_04[0x2c];
    char unk_30[0x30];
    char unk_60[0x20];
} Func02032564Ctx;

Func02032564Ctx *func_02032564(Func02032564Ctx *p)
{
    p->unk_00 = &data_020da1b4;
    __cxa_vec_ctor(p->unk_30, 4, 12, func_020012e8, func_020012dc);
    __cxa_vec_ctor(p->unk_60, 4, 8, func_02032550, func_0202f2f0);
    func_020325b8(p);
    return p;
}
