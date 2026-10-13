/* func_02081cec @ 0x02081cec, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x6c];
    signed char value;
} UnkStruct_02081cec;

extern void func_02081d18(UnkStruct_02081cec *p, signed char val);

signed char func_02081cec(UnkStruct_02081cec *p, int delta)
{
    int clamped;

    clamped = p->value + delta;
    if (clamped > 127) {
        clamped = 127;
    } else if (clamped < -128) {
        clamped = -128;
    }

    func_02081d18(p, (signed char) clamped);
    return (signed char) clamped;
}
