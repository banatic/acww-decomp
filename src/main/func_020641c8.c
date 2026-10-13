/* func_020641c8 @ 0x020641c8, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_020641c8 UnkStruct_020641c8;
struct UnkStruct_020641c8 {
    void *vt;
};

extern void func_020a8cac(UnkStruct_020641c8 *self);
extern char data_020de694;

UnkStruct_020641c8 *func_020641c8(UnkStruct_020641c8 *self)
{
    func_020a8cac(self);
    self->vt = &data_020de694;
    return self;
}
