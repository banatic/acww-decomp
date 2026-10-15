/* func_02027540 @ 0x02027540, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0208150c(unsigned int object);
extern int func_020036e8(unsigned char *object);
extern int func_0202da38(int object, int out, unsigned char *flag, int count, int base, int offset, int scale, int multiplier,
                         int selected);

extern struct {
    int field0;
    unsigned char field4;
} data_020c8e00;

typedef struct {
    void *ptr;
    unsigned char byte;
} UnkStruct_02027540;

void func_02027540(void *self, UnkStruct_02027540 *out)
{
    int local0, local1, local2, local3, local4;
    void *p1;
    void *p2;

    p1 = *(void **) ((char *) self + 0x100);
    p2 = *(void **) ((char *) p1 + 0x830);

    local0 = func_020036e8((unsigned char *) func_0208150c((unsigned int) p2));
    local1 = data_020c8e00.field0;
    local2 = data_020c8e00.field4;
    local3 = 0;
    local4 = 0;

    func_0202da38((int) self, (int) ((char *) self + 0x104), (unsigned char *) self + 0x122, 30, local0, local1, local2,
                  local3, local4);

    out->ptr = (char *) self + 0x104;
    out->byte = *(unsigned char *) ((unsigned char *) self + 0x122);
}
