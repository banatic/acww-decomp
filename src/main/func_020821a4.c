/* func_020821a4 @ 0x020821a4, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct Something {
    void *unk_00;
} Something;

extern void *func_020a8c38(Something *self);
extern char data_020e1904;

Something *func_020821a4(Something *self)
{
    self->unk_00 = (void *) &data_020e1904;
    func_020a8c38(self);
    return self;
}
