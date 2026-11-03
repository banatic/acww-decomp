/* etc_board: 3 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0220bf48 @ 0x0220bf48, 0x4 bytes, Thumb
 * func_ov003_0220bf18 @ 0x0220bf18, 0x30 bytes, Thumb
 * func_ov003_0220bf00 @ 0x0220bf00, 0x18 bytes, Thumb
 */

struct UnkStruct_0220bf18 {
    int unk_00;
    int unk_04;
};

struct UnkStruct_0220bf18_2 {
    char pad_00[0xec];
    char unk_EC[0x40];
    struct UnkStruct_0220bf18 *unk_12C;
};

extern void func_0203ee08(struct UnkStruct_0220bf18_2 *obj, char *ptr);
extern int func_0203e020(struct UnkStruct_0220bf18_2 *obj);
extern int data_ov003_0223c5f4[];

int func_ov003_0220bf48(void *object)
{
    return 1;
}

void func_ov003_0220bf18(struct UnkStruct_0220bf18_2 *obj)
{
    if (obj->unk_12C && obj->unk_12C->unk_04 == 0) {
        char *p = (char *) obj;
        if (p) {
            p += 0xec;
        }
        func_0203ee08(obj, p);
        func_0203e020(obj);
    }
}

int func_ov003_0220bf00(int index)
{
    if (index >= 0 && index < 8) {
        return data_ov003_0223c5f4[index];
    }
    return 0;
}
