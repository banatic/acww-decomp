/* func_020bdb24 @ 0x020bdb24, 0xbc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020bdc50(void *p, int a, int b, int c, int d);

typedef struct {
    unsigned char pad_00[0x24];
    unsigned int unk_24;
    unsigned char pad1[0xc];
    unsigned int unk_34;
} Glob;

typedef struct {
    unsigned char pad_00[0x2f08];
    unsigned int unk_2F08;
    unsigned int unk_2F0C;
    unsigned char pad1[0x44];
    unsigned int unk_2F54;
} UnkStruct_020bdb24;

extern Glob data_021f8ab0;

void func_020bdb24(UnkStruct_020bdb24 *obj)
{
    unsigned int is3 = (data_021f8ab0.unk_24 == 3);
    unsigned int is4 = (data_021f8ab0.unk_24 == 4);

    if (is3 != 0 || is4 != 0) {
        unsigned int state = data_021f8ab0.unk_34;
        int r6 = 13;
        if (state == 1) {
            r6 = 0;
        } else if (state == 2) {
            r6 = 1;
        }

        obj->unk_2F08 = 0x6400;
        obj->unk_2F0C = 0x32;

        if (r6 != 13) {
            int limit = (is3 != 0) ? 0xf : 0x14;
            int arg = 0;
            int i;
            for (i = 0; i < limit; i++) {
                func_020bdc50(obj, r6, 0x3c, arg, 1);
            }
        }

        if (is3 != 0) {
            obj->unk_2F54 = 0x800;
        } else {
            obj->unk_2F54 = 0x1000;
        }
    } else {
        obj->unk_2F08 = 0;
        obj->unk_2F0C = 0;
        obj->unk_2F54 = 0;
    }
}
