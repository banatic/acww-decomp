/* func_0209fba0 @ 0x0209fba0, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern __thumb void *func_020a256c(void *);
extern void func_020ee62c(void *);
extern void func_020edf54(void *);
extern const int data_020e3ae8;
extern const int data_020da13c;

void *func_0209fba0(void *p)
{
    *(unsigned int *) p = (unsigned int) &data_020e3ae8;
    func_020a256c((char *) p + 0x54);
    *(unsigned int *) p = (unsigned int) &data_020da13c;
    func_020ee62c(p);
    func_020edf54(p);
    return p;
}
