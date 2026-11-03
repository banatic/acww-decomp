/* field_actor_room_states2_3: 2 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02229f60 @ 0x02229f60, 0x58 bytes, Thumb
 * func_ov004_02229f5c @ 0x02229f5c, 0x4 bytes, Thumb
 */

typedef struct {
    unsigned char unk_00;
} UnkStruct_02229f5c;

extern void func_02010f5c(void *self);
extern int func_0201100c(void *self);
extern void func_02010d64(void *self);
extern int func_02010ca4(void *self);
extern void *data_020ccf94;
extern int func_02073908(void *a, int b);
extern void func_ov004_02229fb8(void *self);
extern int func_02008258(void *self, int a);

void func_ov004_02229f60(void *self)
{
    func_02010f5c(self);
    func_0201100c(self);
    func_02010d64(self);
    func_02010ca4(self);
    if (func_02073908(data_020ccf94, *(int *) ((char *) self + 0x800)) != 0) {
        func_ov004_02229fb8(self);
    } else {
        *(int *) ((char *) self + 0x7fc) = func_02008258(self, *(int *) ((char *) self + 0x7f0));
    }
}

void func_ov004_02229f5c(UnkStruct_02229f5c *p, unsigned char v)
{
    p->unk_00 = v;
}
