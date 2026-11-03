/* message_walker_2: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020a9354 @ 0x020a9354, 0x12 bytes, Thumb
 * func_020a9334 @ 0x020a9334, 0x1e bytes, Thumb
 * func_020a9318 @ 0x020a9318, 0x1c bytes, Thumb
 * func_020a9314 @ 0x020a9314, 0x4 bytes, Thumb
 */

struct VTable;

struct UnkStruct_020a9354 {
    struct VTable *vtbl;
    int unk_04;
};

struct VTable {
    void (*func0)(struct UnkStruct_020a9354 *);
    void (*func1)(struct UnkStruct_020a9354 *);
    void (*func2)(struct UnkStruct_020a9354 *);
};

typedef struct {
    unsigned int unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
} UnkStruct_020a9318;

extern void func_020a9cac(void *param1, void *param2);
extern unsigned int *func_020a9cc0(void *ptr);
extern void func_020a9ccc(void *ptr);

void func_020a9354(struct UnkStruct_020a9354 *obj, int val)
{
    obj->unk_04 = val;
    obj->vtbl->func2(obj);
}

void func_020a9334(void *param0, void *param1)
{
    void *r5 = param0;
    void *r4 = param1;

    if (r4 != 0) {
        func_020a9cac((char *) r5 + 8, (char *) r5 + 4);
        *(void **) ((char *) r5 + 4) = r4;
    }
}

void func_020a9318(UnkStruct_020a9318 *arg)
{
    arg->unk_04 = *func_020a9cc0(&arg->unk_08);
    func_020a9ccc(&arg->unk_08);
}

int func_020a9314(void)
{
    return 1;
}
