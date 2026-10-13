/* func_020552ec @ 0x020552ec, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int strcmp(const char *s1, const char *s2);

struct Element156 {
    char data[156];
};

struct UnkStruct_020552ec {
    unsigned int unk_00;
    unsigned int count;
    struct Element156 *array156;
    char (*array16)[16];
};

struct Element156 *func_020552ec(struct UnkStruct_020552ec *s, char *name)
{
    unsigned int count;
    unsigned int i;

    i = 0;
    count = s->count;
    for (; i < count; i++) {
        if (strcmp(name, s->array16[i]) == 0) {
            return &s->array156[i];
        }
    }
    return 0;
}
