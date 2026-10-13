/* func_02006554 @ 0x02006554, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[4];
    int unk_04;
} UnkStruct_02006554;
extern void func_020065a0(void *p);
extern UnkStruct_02006554 *func_0200e86c(void *p, int i);
extern void func_02007364(void *p, UnkStruct_02006554 *e);
extern void func_0200e854(void *p);
extern void func_0200f268(void *p, int k);
void func_02006554(unsigned char *p)
{
    int i;
    int *lim;
    UnkStruct_02006554 *e;
    func_020065a0(p);
    i = 0;
    lim = (int *) (p + 0x7fc);
    for (; i < 0x1e; i++) {
        e = func_0200e86c(p, i);
        if (e == 0) {
            break;
        }
        if (e->unk_04 > *lim) {
            func_02007364(p, e);
        }
    }
    func_0200e854(p);
    func_0200f268(p, 0x17);
}
