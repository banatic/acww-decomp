/* activity_fields_2: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020a1380 @ 0x020a1380, 0x1e bytes, Thumb
 * func_020a1368 @ 0x020a1368, 0x18 bytes, Thumb
 * func_020a1350 @ 0x020a1350, 0x18 bytes, Thumb
 * func_020a1338 @ 0x020a1338, 0x18 bytes, Thumb
 * func_020a132c @ 0x020a132c, 0xc bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0xc4];
    int value;
} UnkStruct_020a1368;

typedef struct {
    char pad_00[0xC8];
    int value;
} UnkStruct_021f3c3c;

struct UnkStruct_020a1338 {
    char pad_00[0xCC];
    void *unk_CC;
};

extern UnkStruct_020a1368 *data_021f3c3c;

unsigned int func_020a132c(void);

int func_020a1380(void)
{
    int result;
    int value;

    if ((int) func_020a132c() != 0) {
        value = (int) func_020a132c();
        result = *(unsigned char *) (value + 0xd6);
    } else {
        result = 0;
    }
    return result;
}

int func_020a1368(void)
{
    if (data_021f3c3c == 0) {
        return 0;
    }
    return data_021f3c3c->value;
}

int func_020a1350(void)
{
    if ((*(UnkStruct_021f3c3c * *) &data_021f3c3c) == 0) {
        return 0;
    }
    return (*(UnkStruct_021f3c3c * *) &data_021f3c3c)->value;
}

void *func_020a1338(void)
{
    struct UnkStruct_020a1338 *p;

    p = (*(struct UnkStruct_020a1338 * *) &data_021f3c3c);
    if (p == 0) {
        return 0;
    }
    return p->unk_CC;
}

unsigned int func_020a132c(void)
{
    return (*(unsigned int *) &data_021f3c3c);
}
