/* func_02039e08 @ 0x02039e08, 0x2a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xb0];
    unsigned int unk_B0;
} UnkStruct_02039e08;

extern void func_020399e4(UnkStruct_02039e08 *);
extern void func_02039928(UnkStruct_02039e08 *);
extern void func_02039a94(UnkStruct_02039e08 *);
extern void func_02039d98(UnkStruct_02039e08 *);

void func_02039e08(UnkStruct_02039e08 *param)
{
    if (param->unk_B0) {
        func_020399e4(param);
        func_02039928(param);
        func_02039a94(param);
        func_02039d98(param);
    }
}
