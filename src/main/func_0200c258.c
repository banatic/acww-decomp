/* func_0200c258 @ 0x0200c258, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0203dfac(void);
extern void *func_020825e8(void *);
extern int func_0200beb8(void *a, int b, int c);
extern struct {
    unsigned short pad0;
    unsigned short field2;
} data_021fbe40;

typedef struct {
    char pad_00[0x13c];
    void *value13c;
    char pad_140[0x170 - 0x140];
    int state170;
} UnkStruct_0200c258;

typedef struct {
    int unk_00, unk_04, unk_08;
} UnkStruct_0200c258_2;

typedef int (*Fn)(void *);

void func_0200c258(UnkStruct_0200c258 *self)
{
    void *ptr = 0;
    int state = self->state170;

    if (state == 2) {
        ptr = self->value13c;
    } else if (state == 1) {
        if (data_021fbe40.field2 & 0x400) {
            ptr = func_0203dfac();
        }
    }

    if (ptr != 0) {
        UnkStruct_0200c258_2 *obj = (UnkStruct_0200c258_2 *) ptr;
        unsigned short local = (unsigned short) obj->unk_08;
        void *res = func_020825e8(&local);
        if (res != 0) {
            Fn fn = *(Fn *) ((char *) *(void **) res + 0xa0);
            int rv = fn(res);
            if (rv != -1) {
                func_0200beb8(self, 5, -1);
            }
        }
    }
}
