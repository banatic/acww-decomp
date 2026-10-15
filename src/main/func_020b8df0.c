/* func_020b8df0 @ 0x020b8df0, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020d2288[];
typedef struct {
    unsigned char pad_00[0x7c];
    int unk_7C;
} UnkStruct_020b8df0;
extern UnkStruct_020b8df0 data_021f6ba0;
extern int data_021f6b20[1];
extern void func_020b889c(int *arg1);

void func_020b8df0(int index)
{
    int value = data_020d2288[index];
    data_021f6ba0.unk_7C = value;
    func_020b889c(data_021f6b20);
}
