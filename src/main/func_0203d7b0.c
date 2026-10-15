/* func_0203d7b0 @ 0x0203d7b0, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char data[0x5c];
} UnkStruct_0203d7b0;
extern UnkStruct_0203d7b0 data_021c6ec4[];
extern int func_020b44bc(UnkStruct_0203d7b0 *ptr, int a);

int func_0203d7b0(int index, int arg1)
{
    return func_020b44bc(&data_021c6ec4[index], arg1);
}
