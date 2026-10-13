/* func_ov003_0221f788 @ 0x0221f788, 0x68 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_0221f3f0(void *);
extern void func_ov003_0221f21c(void *);
extern void func_ov003_0221f110(void *);
extern void func_ov003_0221ef3c(void *);

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
