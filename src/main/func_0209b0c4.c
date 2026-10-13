/* func_0209b0c4 @ 0x0209b0c4, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_020d1a54[];
extern int func_02082438(void *arg, unsigned short *val);

typedef struct {
    unsigned char pad_00[12];
    unsigned char index;
} UnkStruct_0209b0c4;

int func_0209b0c4(UnkStruct_0209b0c4 *s, void *arg)
{
    if (s->index < 5) {
        unsigned short val = data_020d1a54[s->index];
        return func_02082438(arg, &val);
    } else {
        return 0;
    }
}
