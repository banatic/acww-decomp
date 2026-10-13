/* func_02072fcc @ 0x02072fcc, 0x76 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char low : 4;
    unsigned char high : 4;
} Nibble02072fcc;

typedef struct {
    unsigned short unk_00;
    unsigned char data[12];
    unsigned char pad_0E[0x10];
    unsigned short arr[10];
    Nibble02072fcc ver;
} Struct02072fcc;

extern int memcmp(const void *a, const void *b, unsigned int n);
extern int func_0209518c(Struct02072fcc *a, Struct02072fcc *b);

int func_02072fcc(Struct02072fcc *a, Struct02072fcc *b)
{
    unsigned int i;

    if (a->ver.low != b->ver.low) {
        goto fail;
    }
    if (a->ver.high != b->ver.high) {
        goto fail;
    }
    if (a->unk_00 != b->unk_00) {
        goto fail;
    }
    if (memcmp(a->data, b->data, 12) != 0) {
        goto fail;
    }
    if (func_0209518c(a, b) == 0) {
        goto fail;
    }

    for (i = 0; i < 10; i++) {
        if (a->arr[i] != b->arr[i]) {
            return 0;
        }
    }

    return 1;
fail:
    return 0;
}
