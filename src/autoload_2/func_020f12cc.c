/* func_020f12cc @ 0x020f12cc, 0xf0 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

typedef struct {
    unsigned char pad_00[0x38];
    void *h1;                   // 0x38
    unsigned char pad_3C[4];    // 0x3c-0x40
    void *h2;                   // 0x40
    unsigned char pad_44[0x2c]; // 0x44-0x70
    unsigned char unk_70;       // 0x70
} UnkStruct_020f12cc;

typedef struct {
    unsigned char pad_00[0x3a];
    unsigned short itemId;
} Handle;

extern void func_0210b634(void *a, int b, int c);

void func_020f12cc(UnkStruct_020f12cc *self, int p1)
{
    int v = (int) self->unk_70 - 0x80;
    if (v < -128) {
        v = -128;
    } else if (v > 127) {
        v = 127;
    }

    if (p1 == 0) {
        func_0210b634(&self->h1, 0xff, v);
        func_0210b634(&self->h2, 0xff, v);
        return;
    }

    {
        Handle *h = (Handle *) self->h1;
        unsigned int ok = (h != 0);
        if (!ok) {
            return;
        }
        switch (h->itemId) {
            case 0xb:
            case 0x92:
            case 0x93:
            case 0xb3:
                func_0210b634(&self->h1, 0xff, v);
                break;
            default:
                break;
        }
    }
}
