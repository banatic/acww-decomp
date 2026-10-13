/* func_ov078_02278fb0 @ 0x02278fb0, 0x34 bytes, Thumb, module ov078
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov078_02279a9c;
extern void func_02138c48(void *, int, int, void (*)(void));
extern void func_0202eb20(void *);
extern void func_020edb3c(void *);
extern void func_020051b0(void);

typedef struct {
    unsigned int unk_00;
    char pad_04[0xb4];
    char sub;
} UnkStruct_02278fb0;

UnkStruct_02278fb0 *func_ov078_02278fb0(UnkStruct_02278fb0 *self)
{
    self->unk_00 = (unsigned int) &data_ov078_02279a9c;
    func_02138c48((void *) &self->sub, 2, 2, func_020051b0);
    func_0202eb20(self);
    func_020edb3c(self);
    return self;
}
