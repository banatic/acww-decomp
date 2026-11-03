/* text_draw_5: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02051694 @ 0x02051694, 0x22 bytes, Thumb
 * func_0205166c @ 0x0205166c, 0x26 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0x54];
    unsigned char flag;
    unsigned char pad_55[3];
    unsigned int type;
} UnkStruct_02051694;

struct UnkStruct_0205166c {
    char pad_00[0x58];
    int unk_58;
    int unk_5C;
};

extern void func_02051368(void *p);
extern void func_02050f0c(void *);

void func_02051694(UnkStruct_02051694 *p)
{
    p->flag = 1;
    if (p->type == 2) {
        func_02051368(p);
        p->flag = 0;
    }
}

void func_0205166c(struct UnkStruct_0205166c *p, int val)
{
    p->unk_5C = val;
    if (p->unk_58 == 2 && p->unk_5C != -1) {
        func_02050f0c(p);
        p->unk_5C = -1;
    }
}
