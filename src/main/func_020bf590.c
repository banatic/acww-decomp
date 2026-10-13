/* func_020bf590 @ 0x020bf590, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x24];
    int unk_24;
} UnkStruct_020bf590;

typedef struct {
    char data[12];
} UnkStruct_020bf590_2;

extern UnkStruct_020bf590_2 data_021fa678[];
extern void func_020bee3c(void *);
extern void func_020bf924(void *);

void func_020bf590(UnkStruct_020bf590 *param)
{
    int field = param->unk_24;
    if (field != 6) {
        func_020bee3c(&data_021fa678[field]);
    }
    func_020bf924(param);
}
