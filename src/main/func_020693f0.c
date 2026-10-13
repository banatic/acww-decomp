/* func_020693f0 @ 0x020693f0, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206b97c(void *self, unsigned int value);
extern char abs_000014b8;
extern char abs_0000033c;

typedef struct {
    char pad_00[0x24];
    unsigned int unk_24;
} Struct020693f0;

void func_020693f0(Struct020693f0 *self)
{
    unsigned int value = self->unk_24;
    value += (unsigned int) &abs_000014b8;
    value += (unsigned int) &abs_0000033c;
    func_0206b97c(self, value);
}
