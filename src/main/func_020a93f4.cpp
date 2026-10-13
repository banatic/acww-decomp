/* func_020a93f4 @ 0x020a93f4, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_020a93f4 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5(unsigned char *chunk);

    unsigned char *cursor;
};

extern "C" void func_020a93f4(UnkStruct_020a93f4 *self)
{
    unsigned char *chunk;

    chunk = self->cursor;
    self->cursor = chunk + chunk[2];
    self->v5(chunk);
}
