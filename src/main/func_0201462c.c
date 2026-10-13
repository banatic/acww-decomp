/* func_0201462c @ 0x0201462c, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0201462c_3;
typedef void (*ObjFunc)(struct UnkStruct_0201462c_3 *);
struct UnkStruct_0201462c_3 {
    ObjFunc *vtable;
};

extern struct UnkStruct_0201462c_3 *func_020160d4(void *);
extern void func_0203b144(void);
extern void func_02095518(int, int, int);

struct UnkStruct_0201462c {
    char pad_00[0xb];
    unsigned char unk_0B;
    unsigned char unk_0C;
};

struct UnkStruct_0201462c_2 {
    char pad_00[0x4e8];
    unsigned int unk_4E8;
    char pad_4EC[0x148];
    void *unk_634;
};

void func_0201462c(struct UnkStruct_0201462c *a, struct UnkStruct_0201462c_2 *b)
{
    void *p = b->unk_634;
    if (p != 0 && func_020160d4(p) != 0) {
        struct UnkStruct_0201462c_3 *obj = func_020160d4(p);
        obj->vtable[36](obj);
    }
    if (a->unk_0C == 0) {
        func_0203b144();
    }
    if (a->unk_0B == 1) {
        b->unk_4E8 &= ~2;
    }
    func_02095518(0, 0, 4);
}
