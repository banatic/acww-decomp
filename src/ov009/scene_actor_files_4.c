/* scene_actor_files_4: 4 functions, module ov009
 * mwccarm 1.2/base -O4,s
 * func_ov009_02264d48 @ 0x02264d48, 0x18 bytes, Thumb
 * func_ov009_02264d30 @ 0x02264d30, 0x18 bytes, Thumb
 * func_ov009_02264d18 @ 0x02264d18, 0x18 bytes, Thumb
 * func_ov009_02264cf8 @ 0x02264cf8, 0x20 bytes, Thumb
 */

extern int func_ov009_02264884(void *argument0);

int func_ov009_02264d48(void *argument0)
{
    int *p = (int *) func_ov009_02264884(argument0);
    if (p) {
        return p[2];
    }
    return 0;
}

int func_ov009_02264d30(void *argument0)
{
    int r0;
    r0 = func_ov009_02264884(argument0);
    if (r0 != 0) {
        r0 = *(int *) (r0 + 0xc);
    } else {
        r0 = 0;
    }
    return r0;
}

int func_ov009_02264d18(void *argument0)
{
    int *p;
    int result;

    p = (int *) func_ov009_02264884(argument0);
    if (p != 0) {
        result = p[4];
    } else {
        result = 0;
    }
    return result;
}

unsigned int func_ov009_02264cf8(void *p, unsigned int n)
{
    void *q;
    if (n >= 4) {
        goto fail;
    }
    q = (void *) func_ov009_02264884(p);
    if (q == 0) {
        goto fail;
    }
    return *(unsigned int *) ((char *) q + n * 4 + 0x20);
fail:
    return 0;
}
