/* func_02068c3c @ 0x02068c3c, 0x2e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208a234(void *p);
extern int func_0208a20c(void *p);

struct UnkStruct_02068c3c {
    unsigned char pad_00[0x0c];
    unsigned char sub[0x70];
    unsigned int unk_7C;
};

int func_02068c3c(struct UnkStruct_02068c3c *obj)
{
    if (obj->unk_7C != 0) {
        goto fail;
    }
    if (func_0208a234(&obj->sub) != 3) {
        goto fail;
    }
    if (func_0208a20c(&obj->sub) == 0) {
        goto fail;
    }
    return 1;
fail:
    return 0;
}
