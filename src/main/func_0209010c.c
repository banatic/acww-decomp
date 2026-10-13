/* func_0209010c @ 0x0209010c, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0209010c {
    unsigned char pad_00[0x938];
    unsigned char counter;
};

void func_0209010c(struct UnkStruct_0209010c *s)
{
    int new;
    new = s->counter + 1;
    if (new > 5) {
        new = 5;
    }
    s->counter = new;
}
