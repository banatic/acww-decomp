/* func_02010e10 @ 0x02010e10, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020310c8(int);
extern void func_02010e58(void *p, int *locals, int arg);

typedef struct {
    char pad_00[0x6f4];
    int unk_6F4;
    char pad_6F8[4];
    int unk_6FC;
} UnkStruct_02010e10;

void func_02010e10(UnkStruct_02010e10 *p, int arg)
{
    int locals[3];
    locals[0] = p->unk_6F4;
    locals[1] = func_020310c8(0);
    locals[2] = p->unk_6FC;
    func_02010e58(p, locals, arg);
}
