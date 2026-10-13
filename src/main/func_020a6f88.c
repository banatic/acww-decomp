/* func_020a6f88 @ 0x020a6f88, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_020a6f88 {
    char pad_00[0x64];
    struct UnkStruct_020a6f88 *unk_64;
} UnkStruct_020a6f88;

extern UnkStruct_020a6f88 *data_020ccf94;
extern int func_02073918(UnkStruct_020a6f88 *obj, int arg);
extern int func_020b5e70(void);
extern void func_020a7408(UnkStruct_020a6f88 *obj, int arg);
extern void func_020a7948(void *p);
extern void func_020a7940(void *p, int arg);
extern void func_02073820(UnkStruct_020a6f88 *obj);
extern void func_020737f0(UnkStruct_020a6f88 *obj, void *p, int arg);
extern void func_02073770(UnkStruct_020a6f88 *obj, int arg1, int arg2);
extern void func_020a7944(void *p);

void func_020a6f88(void)
{
    UnkStruct_020a6f88 *obj;
    int local[2];

    obj = data_020ccf94;
    if (func_02073918(obj, 0)) {
        obj = obj->unk_64;
        func_020a7408(obj, func_020b5e70());
    } else {
        func_020a7948(&local);
        func_020a7940(&local, func_020b5e70());
        obj = data_020ccf94;
        func_02073820(obj);
        func_020737f0(obj, &local, 1);
        func_02073770(obj, 8, 0);
        func_020a7944(&local);
    }
}
