/* func_ov004_0220faac @ 0x0220faac, 0xe4 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#pragma opt_propagation off
typedef struct {
    int unk_00, unk_04, unk_08;
} UnkStruct_0220faac;

extern UnkStruct_0220faac data_ov004_02256e58[3];
extern UnkStruct_0220faac data_ov004_02256e64;
extern UnkStruct_0220faac data_ov004_02256e70;
extern int data_ov004_02256c70;
extern int data_ov004_02256de0[3];
extern int data_ov004_02256dec[3];
extern int data_ov004_02256df8[3];
extern void __register_global_object(UnkStruct_0220faac *a, void *destructor, void *c);
extern void func_020012dc(void *arg0);
extern int func_020b65c4(void);
extern int func_ov004_0223d348(void);

void func_ov004_0220faac(char *self, UnkStruct_0220faac *out)
{
    volatile UnkStruct_0220faac t;
    UnkStruct_0220faac *p;
    int i;

    if ((data_ov004_02256c70 & 1) == 0) {
        data_ov004_02256e58[0].unk_00 = 0x2000;
        data_ov004_02256e58[0].unk_04 = 0x2000;
        data_ov004_02256e58[0].unk_08 = 0x2000;
        __register_global_object(data_ov004_02256e58, ((void *) &func_020012dc), &data_ov004_02256de0);
        {
            UnkStruct_0220faac *object = &data_ov004_02256e64;
            int value = 0x4000;
            object->unk_00 = value;
            object->unk_04 = 0x2000;
            object->unk_08 = 0x2000;
            __register_global_object(object, ((void *) &func_020012dc), &data_ov004_02256dec);
        }
        {
            UnkStruct_0220faac *object = &data_ov004_02256e70;
            int value = 0x4000;
            object->unk_00 = value;
            object->unk_04 = 0x2000;
            object->unk_08 = value;
            __register_global_object(object, ((void *) &func_020012dc), &data_ov004_02256df8);
        }
        data_ov004_02256c70 |= 1;
    }
    func_020b65c4();
    p = &data_ov004_02256e58[*(int *) (self + 0x784)];
    t.unk_00 = p->unk_00;
    t.unk_04 = p->unk_04;
    t.unk_08 = p->unk_08;
    if (*(int *) (self + 0x790) == 0) {
        t.unk_04 = 0x200;
    } else if (func_ov004_0223d348() != 0) {
        t.unk_04 = *(int *) (self + 0x790);
    } else {
        t.unk_04 = *(int *) (self + 0x790) >> 1;
    }
    out->unk_00 = t.unk_00;
    out->unk_04 = t.unk_04;
    out->unk_08 = t.unk_08;
}
