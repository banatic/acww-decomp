/* func_02032844 @ 0x02032844, 0x98 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202fb28(const void *elem, void *arg);
extern int func_0202f9d0(const void *elem, void *local, void *arg, void *ptr);
extern void func_02034280(void *dst, void *src);

typedef struct Output {
    char pad_00[4];
    unsigned int *unk_04;
    char *unk_08;
    char pad1[12];
    unsigned char flag18;
    char pad2[3];
    void *unk_1C;
    char pad_20[4];
    unsigned int unk_24;
    unsigned int unk_28;
    unsigned int unk_2C;
    unsigned int unk_30;
    char pad_34[4];
    unsigned int count38;
} Output;

typedef struct InputElem {
    char pad_00[0x28];
    unsigned int unk_28;
    unsigned int unk_2C;
    unsigned int unk_30;
    char pad1[4];
    unsigned char flag38;
    char pad2[7];
} InputElem;

void func_02032844(Output *out, InputElem *in)
{
    unsigned int local[3];
    InputElem *ptr;
    int ok;
    unsigned int *dst;
    unsigned int *src;

    out->count38 = *(unsigned int *) ((char *) in + 0xa00);

    for (ptr = in; ptr < (InputElem *) ((char *) in + (out->count38 << 6)); ptr++) {
        if (func_0202fb28(ptr, &out->unk_08) < 0) {
            continue;
        }

        ok = (func_0202fb28(ptr, out->unk_04) >= 0) ? 1 : 0;
        if (ok != 0) {
            continue;
        }

        if (func_0202f9d0(ptr, local, &out->unk_08, out->unk_04) == 0) {
            continue;
        }

        dst = out->unk_04;
        dst[0] = local[0];
        dst[1] = local[1];
        dst[2] = local[2];

        func_02034280(&out->unk_1C, &ptr->flag38);

        src = &ptr->unk_28;
        out->unk_24 = src[0];
        out->unk_28 = src[1];
        out->unk_2C = src[2];

        out->unk_30 = ptr->flag38;
        out->flag18 = 1;
    }
}
