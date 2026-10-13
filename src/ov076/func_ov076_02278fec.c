/* func_ov076_02278fec @ 0x02278fec, 0x48 bytes, Thumb, module ov076
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x64];
    int counter;
    char pad_68[0x8e - 0x64 - 4];
    unsigned short flags_low;
    char pad_90[0x94 - 0x8e - 2];
    unsigned short flags_high;
    char pad_96[0x350 - 0x94 - 2];
    char sub[1];
    char pad_351[0x720 - 0x350 - 1];
    int threshold;
} UnkStruct_02278fec;

extern void func_0201aff4(void *);
extern void func_020ee470(void *);

int func_ov076_02278fec(UnkStruct_02278fec *self)
{
    self->flags_high = 0;
    self->flags_low = 0;
    func_0201aff4(&self->sub);
    self->counter += 0xeb;
    if (self->counter > (self->threshold + 0x14000)) {
        func_020ee470(self);
    }
    return 1;
}
