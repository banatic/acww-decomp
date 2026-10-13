/* func_0208c178 @ 0x0208c178, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208c008(void *arg);
extern void func_0208c804(void *arg);
extern void func_0208a1f4(void *arg);
extern void func_0208af00(void *arg);
extern void __arm func_020edb3c(void *arg);
extern unsigned char data_020e2234;

typedef struct {
    void *unk_00;
    unsigned char pad_04[0x08];
    void *unk_0C;
    unsigned char pad_10[0x18];
    void *unk_28;
} UnkStruct_0208c178;

UnkStruct_0208c178 *func_0208c178(UnkStruct_0208c178 *p)
{
    p->unk_00 = (void *) &data_020e2234;
    func_0208c008(p);
    func_0208c804(&p->unk_28);
    func_0208a1f4(&p->unk_0C);
    func_0208af00(p);
    func_020edb3c(p);
    return p;
}
