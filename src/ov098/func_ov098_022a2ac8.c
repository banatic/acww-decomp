/* func_ov098_022a2ac8 @ 0x022a2ac8, 0x54 bytes, Thumb, module ov098
 * mwccarm 1.2/base -O4,s
 */

typedef struct GameObj {
    char pad_00[182];
    unsigned char byte_field;
    char pad_B7[11625];
    int int_field1;
    int int_field2;
} GameObj;

extern void func_0204f794(int *out, int a, int b);
extern int func_ov096_0229f0dc(GameObj *self, unsigned char byte);
extern int func_ov003_02219b90(int *a, short *b);
extern void func_ov096_0229f5ac(GameObj *self, unsigned char byte);
extern void func_ov002_02208098(GameObj *self, int param);

void func_ov098_022a2ac8(GameObj *self)
{
    short local_0;
    int local_4[3];

    func_0204f794(local_4, self->int_field1, self->int_field2);
    local_0 = (short) func_ov096_0229f0dc(self, self->byte_field);
    if (func_ov003_02219b90(local_4, &local_0) != 0) {
        func_ov096_0229f5ac(self, self->byte_field);
        func_ov002_02208098(self, 0x2f);
    }
}
