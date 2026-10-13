/* func_020a6f20 @ 0x020a6f20, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_021f4320;
extern void func_020a5bc4(void *a, void *b, void *c);

void func_020a6f20(void *a, void *b)
{
    ((void (*)(void *, void *, void *)) &func_020a5bc4)(&data_021f4320, a, b);
}
