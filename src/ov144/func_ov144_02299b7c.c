/* func_ov144_02299b7c @ 0x02299b7c, 0x80 bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov144_02299c2c(void *p, int n);
extern void func_ov144_02299c8c(void *p, int n);
extern void func_ov144_02299c5c(void *p, int n);

typedef struct {
    char pad_00[0xba];
    short unk_BA;
    short unk_BC;
} UnkStruct_02299b7c;

void func_ov144_02299b7c(UnkStruct_02299b7c *p)
{
    if (p->unk_BA == -1) {
        func_ov144_02299c2c(p, 7);
        if (p->unk_BC == -1) {
            func_ov144_02299c8c(p, 0x59);
            func_ov144_02299c5c(p, 7);
        } else {
            func_ov144_02299c8c(p, 0x69);
            func_ov144_02299c5c(p, 8);
        }
    } else {
        func_ov144_02299c2c(p, 6);
        if (p->unk_BC == -1) {
            func_ov144_02299c8c(p, 0x59);
            func_ov144_02299c5c(p, 6);
        } else {
            func_ov144_02299c8c(p, 0x69);
            func_ov144_02299c5c(p, 8);
        }
    }
}
