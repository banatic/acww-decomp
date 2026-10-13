/* func_ov114_0229d1dc @ 0x0229d1dc, 0x44 bytes, Thumb, module ov114
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char data[0x9f];
} UnkStruct_0229d1dc_2;

typedef struct {
    char pad_00[0x121c];
    UnkStruct_0229d1dc_2 sub;
    unsigned char flag;
} UnkStruct_0229d1dc;

extern int func_0208e930(UnkStruct_0229d1dc_2 *);
extern void func_ov002_0220a580(UnkStruct_0229d1dc_2 *);

int func_ov114_0229d1dc(UnkStruct_0229d1dc *self)
{
    if (self->flag == 2) {
        if (func_0208e930(&self->sub)) {
            func_ov002_0220a580(&self->sub);
            self->flag = 4;
            return 1;
        }
    } else {
        self->flag = 4;
        return 1;
    }
    return 0;
}
