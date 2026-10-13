/* func_0206c278 @ 0x0206c278, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206c038(void *obj, unsigned int *used_ptr, unsigned int new_used, unsigned int n);

typedef struct {
    char buf[0x400];
    unsigned int used;
} UnkStruct_0206c278;

int func_0206c278(UnkStruct_0206c278 *obj, char *src, unsigned int n)
{
    int ret;
    unsigned int i;

    ret = (0x400 - obj->used > n) ? 1 : 0;
    if (ret) {
        for (i = 0; i < n; i++) {
            ((char *) obj + obj->used)[i] = src[i];
        }
        {
            unsigned int new_used = obj->used + n;
            obj->used = new_used;
            func_0206c038(obj, &obj->used, new_used, n);
        }
    }
    return ret;
}
