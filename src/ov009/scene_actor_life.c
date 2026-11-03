/* scene_actor_life: 2 functions, module ov009
 * mwccarm 1.2/base -O4,s
 * func_ov009_02264c64 @ 0x02264c64, 0x4 bytes, Thumb
 * func_ov009_02264c40 @ 0x02264c40, 0x22 bytes, Thumb
 */

extern void func_0209def4(void *);

int func_ov009_02264c64(void *object)
{
    return 1;
}

int func_ov009_02264c40(void *self)
{
    unsigned char data[4];
    func_0209def4(data);
    if (data[1] >= 6 && data[1] < 18) {
        return 0;
    }
    return 1;
}
