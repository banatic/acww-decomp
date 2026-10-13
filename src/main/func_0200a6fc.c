/* func_0200a6fc @ 0x0200a6fc, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_020ccf94;
extern void func_02010f5c(void *);
extern int func_02073908(unsigned int, unsigned int);
extern void func_0200f530(void *, void *);
extern void func_02010d64(void *);
extern void func_0200a9e0(void *);
extern void func_0200a80c(void *);
extern void func_0200a7e8(void *);

typedef struct {
    unsigned char pad_00[2];
    unsigned char x;
    unsigned char y;
} UnkStruct_0200a6fc;

typedef struct {
    unsigned char pad_00[0x7d4];
    UnkStruct_0200a6fc sub;
    unsigned char pad_7D8[0x800 - 0x7d4 - 4];
    unsigned int unk_800;
} UnkStruct_0200a6fc_2;

void func_0200a6fc(void *this)
{
    UnkStruct_0200a6fc_2 *self = (UnkStruct_0200a6fc_2 *) this;
    struct {
        int x;
        int y;
    } local;
    UnkStruct_0200a6fc *sub;
    int x, y;

    func_02010f5c(this);
    if (func_02073908(data_020ccf94, self->unk_800) != 0) {
        func_02010d64(this);
        func_0200a9e0(this);
        func_0200a80c(this);
    } else {
        sub = &self->sub;
        y = sub->y;
        x = sub->x;
        local.x = x;
        local.y = y;
        func_0200f530(this, &local);
        func_02010d64(this);
        func_0200a9e0(this);
        func_0200a7e8(this);
    }
}
