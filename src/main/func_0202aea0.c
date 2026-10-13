/* func_0202aea0 @ 0x0202aea0, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0202aea0 {
    unsigned char pad_00[0x824];
    unsigned char flag;
};

struct UnkStruct_0202aea0_2 {
    unsigned char pad_00[0x100];
    struct UnkStruct_0202aea0 *inner;
};

struct Pair {
    unsigned int a;
    unsigned int b;
};

extern void MI_CpuFill8(void *, int, int);
extern void func_02015774(struct UnkStruct_0202aea0_2 *, int, void *, int, int);
extern void func_02015828(struct UnkStruct_0202aea0_2 *, int);
extern void func_0202dbf0(struct UnkStruct_0202aea0_2 *, struct Pair);
extern struct Pair data_020d9260;

extern unsigned char data_021c1e84[];

void func_0202aea0(struct UnkStruct_0202aea0_2 *arg0)
{
    MI_CpuFill8((void *) data_021c1e84, 0, 0x40);
    if (arg0->inner->flag == 0) {
        func_02015774(arg0, 0x15, (void *) data_021c1e84, 4, 0);
    } else {
        func_02015774(arg0, 0x16, (void *) data_021c1e84, 0xa, 0);
    }
    func_02015828(arg0, 6);
    func_0202dbf0(arg0, data_020d9260);
}
