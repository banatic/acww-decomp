/* func_02015e10 @ 0x02015e10, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02094fd4(void *);
extern int func_02003618(void *, void *);
extern void func_02068404(void *, void *, void *);
extern void *func_02094fbc(void *);

typedef struct {
    char pad_00[0x40];
    void *unk_40;
} UnkStruct_02015e10;

void func_02015e10(UnkStruct_02015e10 *p, void *arg1, void *arg2)
{
    char local[0x20];

    func_02094fd4(local);
    func_02003618(arg1, local);
    func_02068404(p->unk_40, arg2, local);
    func_02094fbc(local);
}
