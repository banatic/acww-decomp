/* func_0205517c @ 0x0205517c, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020dd05c;
extern char data_020dd06c;
extern void func_02057054(void *ptr);
extern void func_0205572c(void *ptr);

typedef struct {
    unsigned int unk_00;
    char pad_04[0x98];
    unsigned int unk_9C;
} UnkStruct_0205517c;

UnkStruct_0205517c *func_0205517c(UnkStruct_0205517c *param)
{
    param->unk_00 = (unsigned int) &data_020dd05c;
    param->unk_9C = (unsigned int) &data_020dd06c;
    func_02057054(&param->unk_9C);
    func_0205572c(param);
    return param;
}
