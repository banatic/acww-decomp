/* func_020742b4 @ 0x020742b4, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b65c4(void);

struct UnkStruct_020742b4 {
    char pad_00[0x64];
    volatile int unk_64;
};

extern struct UnkStruct_020742b4 *data_020ccf94;
extern void func_02073d74(struct UnkStruct_020742b4 *, int);
extern void func_02073de0(struct UnkStruct_020742b4 *, int, int);
extern void func_02074228(int);
extern void func_020a6c8c(void);
extern void func_020a7394(int, int, int, int, int);

void func_020742b4(void)
{
    struct UnkStruct_020742b4 *obj;
    int ret;

    obj = data_020ccf94;
    func_02073d74(obj, 2);
    obj->unk_64 = 0;
    func_02073de0(obj, obj->unk_64, 1);
    func_02074228(0);
    func_020a6c8c();
    ret = func_020b65c4();
    func_020a7394(0, ret, 1, 0, 7);
}
