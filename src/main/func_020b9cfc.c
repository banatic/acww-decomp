/* func_020b9cfc @ 0x020b9cfc, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ba1cc(void);
extern void func_020ba108(void *ptr);
extern int data_020e5934;

typedef struct UnkStruct_020b9cfc {
    void *vtable;
    unsigned char pad_04[0xc];
    unsigned char sub[1];
} UnkStruct_020b9cfc;

UnkStruct_020b9cfc *func_020b9cfc(UnkStruct_020b9cfc *self)
{
    func_020ba1cc();
    self->vtable = &data_020e5934;
    func_020ba108(self->sub);
    return self;
}
