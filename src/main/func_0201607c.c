/* func_0201607c @ 0x0201607c, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020823e8(void *);

typedef struct {
    char pad_00[0x4c];
    void *unk_4C;
    void *unk_50;
    char pad_54;
    unsigned char unk_55;
} UnkStruct_0201607c;

int func_0201607c(UnkStruct_0201607c *self)
{
    switch (self->unk_55) {
        case 0:
            if (self->unk_4C) {
                return func_020823e8((char *) self->unk_4C + 0xea);
            }
            break;
        case 1:
            if (self->unk_50) {
                return func_020823e8((char *) self->unk_50 + 0xea);
            }
            break;
        default:
            break;
    }
    return 5;
}
