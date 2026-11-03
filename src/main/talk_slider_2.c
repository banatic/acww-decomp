/* talk_slider_2: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020aad8c @ 0x020aad8c, 0xe bytes, Thumb
 * func_020aad7c @ 0x020aad7c, 0xe bytes, Thumb
 * func_020aad5c @ 0x020aad5c, 0x20 bytes, Thumb
 * func_020aad3c @ 0x020aad3c, 0x20 bytes, Thumb
 * func_020aad08 @ 0x020aad08, 0x32 bytes, Thumb
 */

typedef struct {
    char pad_00[0x14];
    void *unk_14;
    char pad_18[0x24 - 0x14 - 4];
    void *unk_24;
    unsigned int unk_28;
} UnkStruct_020aad08;

extern int func_020a7e50(void);
extern unsigned int func_020515b8(void *ptr);

int func_020aad8c(void *r0)
{
    if (*(unsigned int *) ((char *) r0 + 0x2c) == 0) {
        return 1;
    }
    return 0;
}

int func_020aad7c(void *r0)
{
    if (*(unsigned int *) ((char *) r0 + 0x2c) == 1) {
        return 1;
    }
    return 0;
}

int func_020aad5c(void *param)
{
    int result;
    unsigned char *ptr;

    result = func_020aad8c(param);
    if (result != 0) {
        ptr = (unsigned char *) param + 0x30;
        if (*ptr != 0) {
            return 1;
        }
    }
    return 0;
}

int func_020aad3c(void *arg)
{
    return (func_020a7e50() != 0) || (*(unsigned char *) ((char *) arg + 0x31) != 0);
}

void func_020aad08(UnkStruct_020aad08 *obj)
{
    unsigned int max;
    unsigned int v;

    max = 0;
    if (obj->unk_24 != 0) {
        v = func_020515b8(obj->unk_24);
        if (v > max) {
            max = v;
        }
    }
    if (obj->unk_14 != 0) {
        v = func_020515b8(obj->unk_14);
        if (v > max) {
            max = v;
        }
    }
    obj->unk_28 = max;
}
