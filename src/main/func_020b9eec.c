/* func_020b9eec @ 0x020b9eec, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020b9eec_3 {
    int pad_00;
};

struct UnkStruct_020b9eec {
    char data[0x10];
    struct UnkStruct_020b9eec_3 sub;
};

struct UnkStruct_020b9eec_2 {
    int unk_00;
    int unk_04;
};

extern void func_020b9ed8(struct UnkStruct_020b9eec *a);
extern void func_020ba1a8(struct UnkStruct_020b9eec_3 *sub, int flag, struct UnkStruct_020b9eec_2 *b, int word4);
extern char func_020ba118(struct UnkStruct_020b9eec_3 *sub);
extern int func_020b9978(struct UnkStruct_020b9eec *a);
extern void func_020ba004(struct UnkStruct_020b9eec *a);

int func_020b9eec(struct UnkStruct_020b9eec *a, struct UnkStruct_020b9eec_2 *b, int c)
{
    func_020b9ed8(a);
    a->data[0xe] = 0;
    func_020ba1a8(&a->sub, 0, b, b->unk_04);
    a->data[0xf] = func_020ba118(&a->sub);
    a->data[0xc] = c;
    if (func_020b9978(a) != 0) {
        return 1;
    }
    func_020ba004(a);
    return 0;
}
