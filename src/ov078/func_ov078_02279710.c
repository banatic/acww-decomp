/* func_ov078_02279710 @ 0x02279710, 0x28 bytes, Thumb, module ov078
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202ec14(void *);
extern int func_0208602c(void);
extern int func_020860b8(int);
extern void func_02087864(int, int, int);

struct UnkStruct_02279710 {
    char pad_00[0x5c];
    int unk_5C;
    char pad_60[4];
    int unk_64;
};

int func_ov078_02279710(struct UnkStruct_02279710 *param)
{
    int ret = func_0202ec14(param);
    if (ret == 0) {
        return 0;
    }
    func_02087864(func_020860b8(func_0208602c()), param->unk_5C, param->unk_64);
    return 1;
}
