/* func_0201e4d4 @ 0x0201e4d4, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct InputStruct {
    unsigned char pad_00[0x104];
    unsigned int field_at_104;
    unsigned char pad_108[0x1A];
    unsigned char byte_at_122;
} InputStruct;

typedef struct OutputStruct {
    void *ptr_at_0;
    unsigned char byte_at_4;
} OutputStruct;

extern void func_02021118(InputStruct *, OutputStruct *);
extern void func_02022454(InputStruct *);
extern void func_0202dac0(InputStruct *);

void func_0201e4d4(InputStruct *param0, OutputStruct *param1)
{
    func_02021118(param0, param1);
    func_02022454(param0);
    param1->ptr_at_0 = &param0->field_at_104;
    param1->byte_at_4 = param0->byte_at_122;
    func_0202dac0(param0);
}
