/* func_020fa3e4 @ 0x020fa3e4, 0xb4 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern void GX_BeginLoadTexPltt(void);
extern void GX_EndLoadTexPltt(void);
extern void GX_LoadTexPltt(const void *pData, unsigned int format, unsigned int size);

struct UnkStruct_020fa3e4 {
    unsigned int unk_00;
    unsigned int type : 4;
    unsigned int : 28;
    unsigned int unk_08;
    unsigned int unk_0C;
    unsigned int unk_10;
};

struct Entry {
    struct UnkStruct_020fa3e4 *p;
    unsigned int pad_04;
    unsigned int result;
    unsigned int pad_0C;
    unsigned int pad_10;
};

struct UnkStruct_020fa3e4_2 {
    char pad_00[0x20];
    struct Entry *entries;
    char pad_24[2];
    unsigned short count;
};

int func_020fa3e4(struct UnkStruct_020fa3e4_2 *self, int (*callback)(unsigned int, int))
{
    int i;
    int one = 1;

    GX_BeginLoadTexPltt();

    for (i = 0; i < self->count; i++) {
        struct Entry *e = &self->entries[i];
        struct UnkStruct_020fa3e4 *p = e->p;
        int value = 0;

        if (p->unk_10 != 0) {
            int arg = (p->type == 2) ? one : 0;
            value = callback(p->unk_10, arg);
            GX_LoadTexPltt((char *) e->p + p->unk_0C, value, p->unk_10);
        }

        e->result = value;
    }

    GX_EndLoadTexPltt();
    return 1;
}
