/* func_020b496c @ 0x020b496c, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a8bb8(void *ptr, int arg2);
struct UnkStruct_020b496c {
    unsigned char pad_00[0x5c];
};
extern struct UnkStruct_020b496c data_021f62a8[];
void func_020b496c(int idx, int arg2)
{
    func_020a8bb8(&data_021f62a8[idx], arg2);
}
