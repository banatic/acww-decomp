/* func_020836b8 @ 0x020836b8, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02083c30(void *, unsigned int);
extern int func_02083708(void);
extern void func_020837a8(void *object);

struct UnkStruct_020836b8 {
    int pad_00;
    unsigned int count;
};

unsigned int func_020836b8(struct UnkStruct_020836b8 *p, unsigned int idx)
{
    register unsigned int preserved_result;
    int base;
    int offset;

    func_02083c30(p, idx);
    if (idx >= p->count) {
        return p->count;
    }

    base = func_02083708() + 8;
    offset = idx * 2;
    func_020837a8((void *) (base + offset));
    asm { mov preserved_result, r0 }
    return preserved_result;
}
