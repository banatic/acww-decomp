/* town_ground_3: 3 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0221f788 @ 0x0221f788, 0x68 bytes, Thumb
 * func_ov003_0221f6dc @ 0x0221f6dc, 0xac bytes, Thumb
 * func_ov003_0221f668 @ 0x0221f668, 0x74 bytes, Thumb
 */

typedef struct {
    unsigned char data[0xec];
} Elem;

typedef struct {
    unsigned char pad_00[0x50];
    Elem *array;
    void *unk_54;
    unsigned char pad_58[0xf0];
    int inner;
    int outer;
    void *unk_150;
    unsigned char pad_154[0x1bc];
    void *unk_310;
} UnkStruct_0221f788;

typedef struct {
    unsigned char pad_00[0x5c];
    unsigned char *unk_5C;
} UnkStruct_0221f668;

extern int func_ov003_0221f3f0(void *);
extern int func_ov003_0221f21c(void *);
extern int func_ov003_0221f110(void *);
extern void func_ov003_0221ef3c(void *);
extern void *func_ov003_0221efec(void *, const void *);
extern void *func_ov003_0221ef94(void *);
extern int func_ov003_0221ef90(void *);
extern void func_ov003_0221ef44(void *, void *, unsigned short);
extern void func_ov003_0221efc0(void *);
extern unsigned char data_ov003_0223cad0;
extern void *data_021c67a4;
extern unsigned int data_021c67d0[3];
extern int func_02057a50(void *object, const char *name);
extern int data_ov003_02239a24[2];

int func_ov003_0221f788(UnkStruct_0221f788 *self)
{
    func_ov003_0221f3f0(&self->unk_54);
    {
        int k = 0;
        int i = 0;
        for (i = 0; i < self->outer; i++) {
            int j = 0;
            while (j < self->inner) {
                func_ov003_0221f21c(&self->array[k++]);
                j++;
            }
        }
    }
    func_ov003_0221f110(&self->unk_150);
    func_ov003_0221ef3c(&self->unk_310);
    return 1;
}

void func_ov003_0221f6dc(void *self)
{
    unsigned int tmp[3];
    unsigned char local[0x1c];
    void *ptr;
    int result;
    int id;

    data_ov003_0223cad0 = 0;
    if (data_021c67a4 == 0) {
        return;
    }

    tmp[0] = data_021c67d0[0];
    tmp[1] = data_021c67d0[1];
    tmp[2] = data_021c67d0[2];

    func_ov003_0221efec(local, tmp);
    ptr = func_ov003_0221ef94(local);
    if (ptr != 0) {
        id = 0x80d;
        result = func_ov003_0221ef90(local);
        switch (result) {
            case 0x11:
                id = 0x80b;
                break;
            case 0x12:
                data_ov003_0223cad0 = 1;
                break;
            case 5:
                id = 0x80e;
                break;
            case 0xf:
                id = 0x80c;
                break;
            default:
                break;
        }
        func_ov003_0221ef44((unsigned char *) self + 0x310, ptr, id);
    }
    func_ov003_0221efc0(local);
}

void func_ov003_0221f668(UnkStruct_0221f668 *self, int flag)
{
    unsigned char *res = self->unk_5C;
    unsigned int i;
    unsigned char *block = res + *(int *) (res + 8);
    int zero = 0;

    for (i = 0; i < 2; i++) {
        int idx = func_02057a50((void *) (self->unk_5C), (const char *) (data_ov003_02239a24[i]));
        if (idx != ~zero) {
            unsigned char *recBase = block + 4;
            unsigned short countVal = *(unsigned short *) (block + 0xa);
            unsigned char *entries = recBase + countVal;
            unsigned short strideVal = *(unsigned short *) (recBase + countVal);
            unsigned char *entry = entries + strideVal * idx;
            int off = *(int *) (entry + 4);
            unsigned char *obj = block + off;
            if (obj != 0) {
                int v10 = *(int *) (obj + 0x10);
                v10 |= 0x800;
                *(int *) (obj + 0x10) = v10;
                if (flag) {
                    int vc = *(int *) (obj + 0xc);
                    vc |= 0x800;
                    *(int *) (obj + 0xc) = vc;
                } else {
                    int vc = *(int *) (obj + 0xc);
                    vc &= ~0x800;
                    *(int *) (obj + 0xc) = vc;
                }
            }
        }
    }
}
