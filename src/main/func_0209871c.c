/* func_0209871c @ 0x0209871c, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned short tag;
    unsigned char data[12];
} TaggedData;

typedef struct {
    char pad_00[0x249c];
} Slot;

extern int func_020951bc(const TaggedData *key);
extern TaggedData *func_02099870(Slot *slot);
extern int func_0209518c(const TaggedData *key, const TaggedData *info);
extern int memcmp(const void *s1, const void *s2, unsigned int n);

int func_0209871c(Slot *slots, TaggedData *key)
{
    int i;
    TaggedData *info;

    if (func_020951bc(key) != 1) {
        goto fail;
    }
    i = 0;
    while (i < 4) {
        info = func_02099870(&slots[i]);
        if (key->tag == info->tag) {
            if (memcmp(key->data, info->data, 12) == 0) {
                if (func_0209518c(key, info) != 0) {
                    return i;
                }
            }
        }
        i++;
    }
fail:
    return -1;
}
