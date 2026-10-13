/* func_020339dc @ 0x020339dc, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020da1a4;
extern char data_020da210;
extern void func_0202f8fc(void *dst, int a, int b);
extern void func_020342a4(void *obj);

typedef struct {
    void *ptr;
    char unk_04[8];
    char unk_0C[8];
    char unk_14[12];
    char unk_20[1];
} UnkStruct_020339dc;

void *func_020339dc(UnkStruct_020339dc *self)
{
    self->ptr = (void *) &data_020da1a4;
    func_0202f8fc(&self->unk_04, 0, 0);
    func_0202f8fc(&self->unk_0C, 0, 0);
    func_0202f8fc(&self->unk_14, 0, 0);
    func_020342a4(&self->unk_20);
    self->ptr = (void *) &data_020da210;
    return self;
}
