/* func_02074150 @ 0x02074150, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern struct UnkStruct_02074150 {
    char pad_00[0x64];
    int unk_64;
};
extern struct UnkStruct_02074150 *data_020ccf94;
extern int func_02073dd4(struct UnkStruct_02074150 *p, int field);
extern void func_020a6f64(int value);

void func_02074150(void)
{
    struct UnkStruct_02074150 *p;
    int field;
    p = data_020ccf94;
    field = p->unk_64;
    if (func_02073dd4(p, field) == 0) {
        func_020a6f64(3);
    } else {
        func_020a6f64(field);
    }
}
