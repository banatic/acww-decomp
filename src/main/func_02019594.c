/* func_02019594 @ 0x02019594, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0201afec(void *);
extern void *func_02019de4(void *);
extern void func_0201b1a4(void *, void *, int, int, int);
extern void func_02019af0(void *, int);

void func_02019594(void *a, void *b)
{
    if (*(short *) ((char *) b + 0x8e) == func_0201afec((char *) b + 0x350)) {
        func_0201b1a4((char *) b + 0x350, b, 0, 0, *(unsigned short *) ((char *) func_02019de4(a) + 0x1c));
        func_02019af0(a, 1);
    }
}
