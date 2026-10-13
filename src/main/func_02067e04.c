/* func_02067e04 @ 0x02067e04, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020a7e50(int);
extern int func_020a7ffc(int);
extern int func_020a7e64(int);
extern int func_020a7e44(int);
extern int func_020a812c(int);
extern int func_020a7e70(int);

typedef struct {
    unsigned char pad_00[0x1e98];
    unsigned char byte;
} UnkStruct_02067e04;

int func_02067e04(UnkStruct_02067e04 *self)
{
    int ret = 0;

    if (self->byte == 0) {
        int a = func_020a7e50(self->byte);
        if (a != 0) {
            int b = func_020a7ffc(a);
            if (b != 0) {
                func_020a7e64(b);
                ret = 1;
            }
        } else {
            int c = func_020a7e44(a);
            if (c != 0) {
                int d = func_020a812c(c);
                if (d != 0) {
                    func_020a7e70(d);
                    ret = 1;
                }
            }
        }
    }

    return ret;
}
