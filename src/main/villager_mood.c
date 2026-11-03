/* villager_mood: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0201ca54 @ 0x0201ca54, 0x48 bytes, Thumb
 * func_0201ca40 @ 0x0201ca40, 0x12 bytes, Thumb
 * func_0201ca24 @ 0x0201ca24, 0x1c bytes, Thumb
 * func_0201c9dc @ 0x0201c9dc, 0x48 bytes, Thumb
 * func_0201c9a4 @ 0x0201c9a4, 0x38 bytes, Thumb
 */

struct UnkStruct_0201ca54 {
    char pad_00[0x48];
    unsigned char unk_48;
};

struct GlobalData {
    unsigned int unk_00;
    unsigned int unk_04;
};

struct Object {
    unsigned char pad_00[0x48];
    unsigned char flag;
    struct GlobalData data;
};

extern int func_0201cb68(void *p, int q);
extern void func_0201cab8(void *p, int q);
extern int func_0201cbec(int, int, int, int);
extern struct GlobalData data_020d8f80;
extern int func_020164a0(int a, int b);
extern int data_020c8ed4[5];

void func_0201ca54(struct UnkStruct_0201ca54 *p0, int p1)
{
    if (func_0201cb68(p0, p1) != 0) {
        if (p0->unk_48 == 0) {
            func_0201cab8(p0, p1);
        }
        p0->unk_48 = p0->unk_48 + 1;
        if (p0->unk_48 >= 20U) {
            p0->unk_48 = 0;
        }
    }
}

void func_0201ca40(int a, int b)
{
    func_0201cbec(a, b, 0x62, 0x7f);
}

int func_0201ca24(struct Object *obj, int event)
{
    obj->flag = 0;
    obj->data = data_020d8f80;
    return 1;
}

void func_0201c9dc(unsigned char *p, int q)
{
    if (func_0201cb68((void *) p, q)) {
        if (*(unsigned char *) (p + 0x48) == 0) {
            func_0201ca40((int) p, q);
        }
        *(unsigned char *) (p + 0x48) = *(unsigned char *) (p + 0x48) + 1;
        if (*(unsigned char *) (p + 0x48) >= 14) {
            *(unsigned char *) (p + 0x48) = 0;
        }
    }
}

int func_0201c9a4(int a, int b)
{
    int result = func_020164a0(b + 0x334, 0);
    int *p = data_020c8ed4;
    int i = 0;
    for (; i < 5; p++, i++) {
        if (result == *p) {
            return 1;
        }
    }
    return 0;
}
