/* func_0203a3a4 @ 0x0203a3a4, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a88ec(void *, int, int);
extern unsigned char data_020da628[];

typedef struct {
    void *unk_00;
    char pad_04[12];
    int unk_10;
    int unk_14;
} UnkStruct_0203a3a4;

UnkStruct_0203a3a4 *func_0203a3a4(UnkStruct_0203a3a4 *p, int a, int b)
{
    func_020a88ec(p, a, b);
    p->unk_00 = data_020da628;
    p->unk_10 = a;
    p->unk_14 = b;
    return p;
}
