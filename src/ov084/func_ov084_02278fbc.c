/* func_ov084_02278fbc @ 0x02278fbc, 0x24 bytes, Thumb, module ov084
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov084_0227941c;
extern void *func_0202eb70(void *);

struct UnkStruct_02278fbc {
    int *unk_00;
    char pad_04[0xb4];
    unsigned short unk_B8;
};

struct UnkStruct_02278fbc *func_ov084_02278fbc(struct UnkStruct_02278fbc *param)
{
    func_0202eb70(param);
    param->unk_00 = &data_ov084_0227941c;
    param->unk_B8 = 0xfff1;
    return param;
}
