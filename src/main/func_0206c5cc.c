/* func_0206c5cc @ 0x0206c5cc, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206d420(void *self, void *addr, unsigned int val);

struct UnkStruct_0206c5cc {
    unsigned char pad_00[0x2c];
    unsigned int unk_2C;
};

struct UnkStruct_0206c5cc_2 {
    unsigned char pad_00[0x5c];
    unsigned char unk_5C;
};

void func_0206c5cc(struct UnkStruct_0206c5cc *self)
{
    unsigned int v = self->unk_2C;
    func_0206d420(self, (void *) &((struct UnkStruct_0206c5cc_2 *) (v + 0x14b8))->unk_5C, v);
}
