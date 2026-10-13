/* func_0202f740 @ 0x0202f740, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int x;
    unsigned int y;
} UnkStruct_0202f740;

typedef struct {
    void *unk_00;
    UnkStruct_0202f740 arr[3];
} UnkStruct_0202f740_2;

extern void func_0202f8fc(UnkStruct_0202f740 *dst, int a, int b);
extern void func_0202f7a0(UnkStruct_0202f740 *dst, int a, int b);
extern void func_0202f6ac(UnkStruct_0202f740_2 *self, int a, int b, UnkStruct_0202f740 *src);
extern char data_020da1a4;

UnkStruct_0202f740_2 *func_0202f740(UnkStruct_0202f740_2 *self, int a1, int a2)
{
    UnkStruct_0202f740 temp;

    self->unk_00 = (void *) &data_020da1a4;
    func_0202f8fc(&self->arr[0], 0, 0);
    func_0202f8fc(&self->arr[1], 0, 0);
    func_0202f8fc(&self->arr[2], 0, 0);
    func_0202f8fc(&temp, 0, 0);
    func_0202f7a0(&temp, a1, a2);
    func_0202f6ac(self, a1, a2, &temp);

    return self;
}
