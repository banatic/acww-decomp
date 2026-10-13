/* func_02083c50 @ 0x02083c50, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02083c50 {
  public:
    virtual char *m0();
    virtual char *m1();
    virtual char *m2();
    virtual char *m3();
    virtual char *m4(int i);
    int count;
};

extern "C" void func_02083c50(UnkStruct_02083c50 *self)
{
    char c = 0;
    int i;
    for (i = 0; i < self->count; i++) {
        char *p = self->m4(i);
        if (p) {
            *p = c;
        }
    }
}
