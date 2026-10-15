/* func_ov079_02278cfc @ 0x02278cfc, 0x20 bytes, Thumb, module ov079
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02278cfc {
    void *vt;
} UnkStruct_02278cfc;

extern unsigned char data_ov079_0227a074;
extern void *func_0202eb20(UnkStruct_02278cfc *self);
extern void func_020edb3c(UnkStruct_02278cfc *self);

UnkStruct_02278cfc *func_ov079_02278cfc(UnkStruct_02278cfc *self)
{
    self->vt = &data_ov079_0227a074;
    func_0202eb20(self);
    func_020edb3c(self);
    return self;
}
