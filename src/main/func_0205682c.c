/* func_0205682c @ 0x0205682c, 0x2e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct elem {
    unsigned char data[0x28];
};

struct unk {
    unsigned char pad_00[0x26];
    unsigned char count;
    unsigned char pad_27;
    struct elem *array;
};

extern void func_02056a38(struct elem *e);
extern void func_020568dc(struct unk *p);

void func_0205682c(struct unk *p)
{
    int i;
    for (i = 0; i < p->count; i++) {
        func_02056a38(&p->array[i]);
    }
    func_020568dc(p);
}
