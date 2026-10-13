/* func_020f3fe0 @ 0x020f3fe0, 0x58 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020f3fe0 {
    void *data;
    char flag;
};

extern void func_020f45c4(struct UnkStruct_020f3fe0 *self);
extern void func_020f65bc(int code, int line);
extern void func_020f5a3c(void);
extern char data_0213ef80;
extern char data_021fd1bc[];

struct UnkStruct_020f3fe0 *func_020f3fe0(struct UnkStruct_020f3fe0 *self)
{
    int x;

    func_020f45c4(self);
    self->data = &data_0213ef80;
    x = *(int *) (data_021fd1bc + 0x30);
    if (x != 0) {
        func_020f65bc(x, 0xD1);
    }
    self->flag = 1;
    func_020f5a3c();
    data_021fd1bc[0x73] = 0;
    return self;
}
