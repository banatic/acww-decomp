/* func_020aa82c @ 0x020aa82c, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020e408c;

struct _func_020aa82c_s {
    char *ptr;
    unsigned char byte;
};

void func_020aa82c(struct _func_020aa82c_s *s)
{
    s->ptr = &data_020e408c;
    s->byte = 0;
}
