/* func_ov096_022a04f4 @ 0x022a04f4, 0x48 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_022a04f4 {
    char pad_00[0xB7];
    unsigned char byte_at_B7;
} UnkStruct_022a04f4;

extern int func_ov002_02209f70(void *p);
extern void func_ov096_0229e7c4(UnkStruct_022a04f4 *p, unsigned char b);
extern void func_ov096_0229c2ec(UnkStruct_022a04f4 *p, int n);
extern void func_ov002_02208098(UnkStruct_022a04f4 *p, int n);
extern void func_ov096_0229eb14(UnkStruct_022a04f4 *p);

void func_ov096_022a04f4(UnkStruct_022a04f4 *obj)
{
    if (func_ov002_02209f70((char *) obj + 0x2500) == 0) {
        func_ov096_0229e7c4(obj, obj->byte_at_B7);
        func_ov096_0229c2ec(obj, 0x40);
        func_ov002_02208098(obj, 0x16);
        func_ov096_0229eb14(obj);
    } else {
        func_ov002_02208098(obj, 0xA);
    }
}
