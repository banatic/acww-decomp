/* func_0205996c @ 0x0205996c, 0x3a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0205996c {
    char pad_00[0xcc];
    void *unk_CC[2];
};

extern int func_0203efbc(void *x);

int func_0205996c(struct UnkStruct_0205996c *p, void *q, unsigned int i)
{
    if (i < 2) {
        if (p->unk_CC[i] != 0 && func_0203efbc(q) == func_0203efbc(*(void **) ((char *) p + i * 4 + 0xcc))) {
            return 1;
        }
    }
    return 0;
}
