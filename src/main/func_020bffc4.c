/* func_020bffc4 @ 0x020bffc4, 0x78 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020bffc4 {
    char pad_00[0x34];
    int unk_34;
    int unk_38;
    char pad_3C[0x20];
    char unk_5C;
    char pad_5D[0xf];
    int unk_6C;
    int unk_70;
};

extern void func_020c0084(struct UnkStruct_020bffc4 *a, int b);
extern void func_020c0324(int *a, int b, int c, int d);
extern void func_020bf220(struct UnkStruct_020bffc4 *a, int b, int c);
extern void func_02065268(int a);

void func_020bffc4(struct UnkStruct_020bffc4 *obj, unsigned int b)
{
    int flag;
    int t;
    int r1, r2;

    if ((b >> 31) & 1) {
        flag = 1;
    } else {
        flag = 0;
    }

    func_020c0084(obj, 0);

    obj->unk_6C = obj->unk_34;
    obj->unk_70 = obj->unk_38;

    func_020c0324(&obj->unk_34, obj->unk_6C, obj->unk_70, flag);

    if (flag) {
        r2 = 0x804;
    } else {
        r2 = 0x803;
    }

    t = (b >> 8) & 3;

    if (flag) {
        r1 = 1;
    } else {
        r1 = t + 2;
    }

    func_020bf220(obj, r1, r2);

    if (flag) {
        obj->unk_5C = 4;
        func_02065268(t + 5);
    } else {
        func_02065268(t + 1);
    }
}
