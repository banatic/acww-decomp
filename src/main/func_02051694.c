/* func_02051694 @ 0x02051694, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02051368(void *p);

typedef struct {
    unsigned char pad_00[0x54];
    unsigned char flag;
    unsigned char pad_55[3];
    unsigned int type;
} UnkStruct_02051694;

void func_02051694(UnkStruct_02051694 *p)
{
    p->flag = 1;
    if (p->type == 2) {
        func_02051368(p);
        p->flag = 0;
    }
}
