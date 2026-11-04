/* letter_storage_14: 3 functions, module ov105
 * mwccarm 1.2/base -O4,s
 * func_ov105_0229d870 @ 0x0229d870, 0x98 bytes, Thumb
 * func_ov105_0229d82c @ 0x0229d82c, 0x44 bytes, Thumb
 * func_ov105_0229d7f4 @ 0x0229d7f4, 0x38 bytes, Thumb
 */

typedef struct {
    char pad_00[0xac];
    int unk_AC;
    int unk_B0;
    char pad_B4[0x2b7 - 0xb4];
    unsigned char unk_2B7;
    char pad_2B8[0x248c - 0x2b8];
    unsigned char unk_248C;
} UnkStruct_0229d870;

typedef struct UnkStruct_0229d7f4 {
    char pad_00[0xac];
    int unk_AC;
    int unk_B0;
} UnkStruct_0229d7f4;

void func_ov002_02209d68(void *p, int a, int b);
int func_ov002_02209d38(void *p, int a, int b, int c);
int func_ov002_02209d8c(void *p);
unsigned char *func_ov002_02208098(void *p, unsigned char value);
int func_ov105_0229d4c4(UnkStruct_0229d870 *self, int param2);
int func_ov105_0229d73c(UnkStruct_0229d870 *self, int param2);
int func_ov105_0229d530(UnkStruct_0229d870 *self, int param2);
void func_ov105_0229d154(UnkStruct_0229d870 *self);
void func_ov105_0229c330(UnkStruct_0229d870 *self, int a);
void func_ov105_0229c320(UnkStruct_0229d870 *self, int a);
extern int func_ov105_0229d75c(int, unsigned int arg1);
extern int func_ov105_0229d7d4(void *receiver);
extern int func_ov105_0229d76c(int, unsigned int arg1);
extern int func_ov105_0229d78c(int);
extern void func_ov105_0229d0f8(void *a, void *b);

void func_ov105_0229d870(UnkStruct_0229d870 *self, int param2, int param3)
{
    int r6;
    int v1;

    self->unk_2B7 = param2;

    func_ov002_02209d68(&self->unk_248C, self->unk_AC, self->unk_B0);

    r6 = func_ov105_0229d4c4(self, param2);

    if (func_ov105_0229d73c(self, param2) != 0) {
        r6 -= 8;
    }

    v1 = func_ov105_0229d530(self, param2);

    func_ov002_02209d38(&self->unk_248C, v1, r6, param3);

    func_ov002_02209d8c(&self->unk_248C);

    func_ov105_0229d154(self);

    if (func_ov105_0229d73c(self, param2) != 0) {
        func_ov105_0229c330(self, 0x2000);
    } else {
        func_ov105_0229c320(self, 0x2000);
    }

    func_ov002_02208098(self, 0x15);
}

void func_ov105_0229d82c(int a, int b, int c)
{
    int x = 0x40;
    if (c >= 0xc0) {
        if (func_ov105_0229d75c(a, b) != 0) {
            x = func_ov105_0229d7d4((void *) a);
        }
    } else {
        if (func_ov105_0229d76c(a, b) != 0) {
            x = func_ov105_0229d78c(a);
        }
    }
    if (x != 0x40) {
        b = x;
    }
    func_ov105_0229d870((UnkStruct_0229d870 *) a, b, 4);
}

void func_ov105_0229d7f4(UnkStruct_0229d7f4 *a, void *b, void *c)
{
    func_ov105_0229d0f8(a, b);
    a->unk_AC = func_ov105_0229d530((UnkStruct_0229d870 *) a, (int) b);
    a->unk_B0 = func_ov105_0229d4c4((UnkStruct_0229d870 *) a, (int) b);
    func_ov105_0229d870((UnkStruct_0229d870 *) a, (int) c, 4);
}
