/* func_02083110 @ 0x02083110, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char *func_020831c0(void);

typedef struct {
    unsigned int unk_00;
    unsigned int count;
} self_t;

char *func_02083110(self_t *self, unsigned int index)
{
    if (index < self->count) {
        char *p = func_020831c0() + 8;
        return p + index * 0x6C + 4;
    } else {
        return 0;
    }
}
