/* func_020ab558 @ 0x020ab558, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char data[0x90];
} Elem;
typedef struct {
    Elem arr[5];
    int unk_2D0;
    int unk_2D4;
} Big;

extern void func_020ab79c(Elem *e);

void func_020ab558(Big *p)
{
    unsigned int i = 0;
    goto test;
loop:
    func_020ab79c(&p->arr[i]);
    i++;
test:
    if (i < 5) {
        goto loop;
    }
    p->unk_2D0 = 0;
    p->unk_2D4 = -1;
}
