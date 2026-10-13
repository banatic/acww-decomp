/* func_0206658c @ 0x0206658c, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00;
    int unk_04;
} UnkStruct_0206658c;

extern void func_0207cec0(void *addr);
extern int func_0208150c(void);
extern void func_02065e60(UnkStruct_0206658c *ptr);
extern void func_020666e4(int *ptr, int value);

extern unsigned char data_021e5a2c[];

void func_0206658c(UnkStruct_0206658c *ptr)
{
    int result;
    func_0207cec0((void *) data_021e5a2c);
    result = func_0208150c();
    func_02065e60(ptr);
    func_020666e4(&ptr->unk_04, result);
}
