/* func_02045d98 @ 0x02045d98, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02045c08(int);
struct UnkStruct_02045d98 {
    char data[16];
};
extern struct UnkStruct_02045d98 data_021c7884[];
extern void func_020465b0(struct UnkStruct_02045d98 *p);

void func_02045d98(int key)
{
    int idx = func_02045c08(key);
    if (idx >= 0) {
        func_020465b0(&data_021c7884[idx]);
    }
}
