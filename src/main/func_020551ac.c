/* func_020551ac @ 0x020551ac, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020dd05c;
extern char data_020dd06c;

void func_02057054(void *ptr);
void *func_0205572c(void *ptr);
void func_020edb3c(void *ptr);

typedef struct {
    void *unk_00;
    char pad_04[0x98];
    void *unk_9C;
} UnkStruct_020551ac;

void *func_020551ac(UnkStruct_020551ac *self)
{
    self->unk_00 = &data_020dd05c;
    self->unk_9C = &data_020dd06c;
    func_02057054(&self->unk_9C);
    func_0205572c(self);
    func_020edb3c(self);
    return self;
}
