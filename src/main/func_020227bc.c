/* func_020227bc @ 0x020227bc, 0x84 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

extern void func_0202e118(void *dst, void *src);
extern void func_02022bbc(void *p, int n, void *data);
extern int func_0204f61c(void *, int, int, int);
extern unsigned char data_020c8d00[];
extern void *data_021c80bc;

struct UnkStruct_020227bc {
    int a;
    int pad_04;
    int b;
};

struct UnkStruct_020227bc_2 {
    unsigned char pad_00[0x5c];
    struct UnkStruct_020227bc inner;
};

struct UnkStruct_020227bc_3 {
    unsigned char pad_00[0x100];
    struct UnkStruct_020227bc_2 *unk_100;
};

int func_020227bc(struct UnkStruct_020227bc_3 *obj)
{
    unsigned short result;
    unsigned short b;
    unsigned short a;
    void *g;
    unsigned int flag;

    g = data_021c80bc;
    func_0202e118(&result, obj->unk_100);
    flag = 0;
    if (g) {
        struct UnkStruct_020227bc_2 *ip = obj->unk_100;
        struct UnkStruct_020227bc *sp = &ip->inner;
        int x = sp->a >> 17;
        int y = sp->b >> 17;
        if (func_0204f61c(g, x, y, 8)) {
            flag = 1;
        }
    }
    if (flag > 0) {
        b = *(volatile unsigned short *) &result;
        a = *(volatile unsigned short *) &result;
        if (a == 0xfff1 || (b >= 0x1380 && b <= 0x139f)) {
            func_02022bbc(obj, 6, data_020c8d00);
            return 1;
        }
    }
    return 0;
}
