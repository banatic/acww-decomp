/* func_0203f53c @ 0x0203f53c, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0203f53c {
    char data[28];
};

extern struct UnkStruct_0203f53c data_021c72e8[15];
extern void func_0203f58c(struct UnkStruct_0203f53c *p);
extern void MI_CpuFill8(void *p, int a, int b);

void func_0203f53c(void)
{
    int i;
    for (i = 0; i < 15; i++) {
        func_0203f58c(&data_021c72e8[i]);
    }
    MI_CpuFill8(data_021c72e8, 0, 15);
}
