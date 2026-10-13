/* func_02045eec @ 0x02045eec, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0204629c(void *ptr);
typedef struct {
    int unk_00, unk_04, unk_08, unk_0C;
} UnkStruct_02045eec;
extern UnkStruct_02045eec data_021c7884[];

void func_02045eec(int index)
{
    if (index >= 0) {
        func_0204629c(&data_021c7884[index]);
    }
}
