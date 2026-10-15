/* func_02068be4 @ 0x02068be4, 0x2a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208fbd8(char *a, char *b, char *c);
extern int func_0208fbf0(char *a);

typedef struct {
    char pad_00[0x50];
    char data[0x24];
    char *ptr1;
    char *ptr2;
    int counter;
} UnkStruct_02068be4;

void func_02068be4(UnkStruct_02068be4 *p)
{
    func_0208fbd8(p->data, p->ptr1 + 0x59, p->ptr2 + 0x4b);
    func_0208fbf0(p->data);
    if (p->counter > 0) {
        p->counter--;
    }
}
