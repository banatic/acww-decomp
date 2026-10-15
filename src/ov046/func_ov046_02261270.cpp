/* func_ov046_02261270 @ 0x02261270, 0x30 bytes, Thumb, module ov046
 * mwccarm 1.2/base -O4,s
 */
extern "C" int func_020b1558(void);
class UnkStruct_02261270 {
  public:
    virtual void slot00_02261270();
    virtual void slot04_02261270();
    virtual void slot08_02261270();
    char pad04[0xb0];
    int value;
    char padb8[0x0c];
    unsigned char state;
    unsigned char count;
};
extern "C" void func_ov046_02261270(UnkStruct_02261270 *self, int value)
{
    self->slot08_02261270();
    self->value = value;
    self->state = 0;
    self->count = 0x10 - func_020b1558();
}
