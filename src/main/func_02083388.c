/* func_02083388 @ 0x02083388, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02083ca8(void *ptr, int n);
extern void func_020833d4(void);
extern void func_020833ec(void);
extern void func_02138d6c(void *ptr, int a, int b, void (*cb1)(void), void (*cb2)(void));
extern int data_020e1b38;

typedef struct {
    void *unk_00;
    int unk_04;
    char buffer[1];
} UnkStruct_02083388;

void *func_02083388(void *self)
{
    void (*cb2)(void);
    UnkStruct_02083388 *s = (UnkStruct_02083388 *) self;

    func_02083ca8(self, 5);
    s->unk_00 = &data_020e1b38;
    cb2 = func_020833d4;
    func_02138d6c(s->buffer, 5, 2, func_020833ec, cb2);
    return self;
}
