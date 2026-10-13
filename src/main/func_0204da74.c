/* func_0204da74 @ 0x0204da74, 0x36 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    void *unk_00;
    unsigned char pad_04[0x18];
    int unk_1C;
    void *unk_20;
} UnkStruct_0204da74;
extern void func_020e993c(void *q, void *v);
extern void func_02030bac(int a);
void func_0204da74(UnkStruct_0204da74 *p, void *q)
{
    if (p->unk_00 != 0) {
        func_020e993c(q, p->unk_00);
        p->unk_00 = 0;
    }
    if (p->unk_20 != 0) {
        func_020e993c(q, p->unk_20);
        p->unk_20 = 0;
    }
    func_02030bac(p->unk_1C);
}
