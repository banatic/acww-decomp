/* func_0208b5ec @ 0x0208b5ec, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020e21d4;
extern void *func_0208df44(void *);
extern void *func_0208d338(void *);
extern void *func_0208c1dc(void *);
extern void *func_0208bbbc(void *);

typedef struct {
    void *unk_00;
    int unk_04;
    char pad_08[0x340];
    unsigned char byte0;
    unsigned char byte1;
    unsigned char byte2;
} UnkStruct_0208b5ec;

UnkStruct_0208b5ec *func_0208b5ec(UnkStruct_0208b5ec *self)
{
    self->unk_00 = &data_020e21d4;
    self->unk_04 = 0;
    func_0208df44((char *) self + 8);
    func_0208d338((char *) self + 0xe0);
    func_0208c1dc((char *) self + 0x1c4);
    func_0208bbbc((char *) self + 0x2c4);
    self->byte0 = 0;
    self->byte1 = 0;
    self->byte2 = 0;
    return self;
}
