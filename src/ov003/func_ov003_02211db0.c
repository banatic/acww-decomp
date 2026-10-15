/* func_ov003_02211db0 @ 0x02211db0, 0x46 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x98];
    int unk_98;
} UnkStruct_02211db0;

extern void func_ov003_02211e38(UnkStruct_02211db0 *obj);
extern int func_0201100c(UnkStruct_02211db0 *obj);
extern void func_02010d64(UnkStruct_02211db0 *obj);
extern unsigned int func_02011398(int a, int b);
extern void func_0201107c(UnkStruct_02211db0 *obj, unsigned int *p);
extern void func_ov003_02211df8(UnkStruct_02211db0 *obj);

void func_ov003_02211db0(UnkStruct_02211db0 *obj)
{
    int val;
    unsigned int result;
    unsigned int tmp;

    func_ov003_02211e38(obj);
    func_0201100c(obj);
    func_02010d64(obj);

    val = obj->unk_98;
    if (val < 0) {
        val = -val;
    }

    result = func_02011398(val, 0);
    tmp = result * -1;

    func_0201107c(obj, &tmp);
    func_ov003_02211df8(obj);
}
