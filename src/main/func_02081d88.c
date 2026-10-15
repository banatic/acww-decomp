/* func_02081d88 @ 0x02081d88, 0x88 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02081d88 {
    unsigned char pad_00[0x7c];
    unsigned short lo : 8;
    unsigned short mode : 3;
    unsigned short hi : 5;
} UnkStruct_02081d88;

extern int func_02081e10(int p0);
extern int func_0209dffc(const unsigned char *);
extern int func_0209e3ac(void *p0, int p1, int p2);
extern int func_0209e380(int p0, void *p1);

int func_02081d88(UnkStruct_02081d88 *self, void *param2)
{
    int x = func_02081e10((int) self);
    unsigned short field = 0;
    int result = 0;
    int w;

    if (func_0209dffc((const unsigned char *) x) == 0) {
        if (func_0209e3ac(param2, x, 0x3f) == 1) {
            w = func_0209e380(x, param2);
            if (w == 0) {
                field = self->mode;
            } else {
                if (w == 1) {
                    field = (unsigned short) (self->mode + 1);
                }
                result = 1;
            }
        } else {
            result = 1;
        }
    } else {
        result = 1;
    }

    if (field > 4) {
        field = 4;
    }

    self->mode = field;
    return result;
}
