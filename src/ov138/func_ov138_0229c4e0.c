/* func_ov138_0229c4e0 @ 0x0229c4e0, 0x38 bytes, Thumb, module ov138
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov138_0229d4e0[];
extern void func_ov134_0229beb0(void *);
extern void func_ov002_0220afdc(void *);
extern void func_ov002_02209cb4(void *);
extern void func_ov002_0220826c(void *);

struct UnkStruct_0229c4e0 {
    void *unk_00;
};

void *func_ov138_0229c4e0(struct UnkStruct_0229c4e0 *obj)
{
    obj->unk_00 = &data_ov138_0229d4e0;
    func_ov134_0229beb0((char *) obj + 0x2c8);
    func_ov002_0220afdc((char *) obj + 0xfc);
    func_ov002_02209cb4((char *) obj + 0x98);
    func_ov002_0220826c(obj);
    return obj;
}
