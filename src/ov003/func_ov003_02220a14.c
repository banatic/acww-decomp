/* func_ov003_02220a14 @ 0x02220a14, 0x130 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_02223b34(void *);
extern void func_02055438(void *);
extern void func_02055764(void *);
extern void func_02138c48(void *, int, int, void (*)(void *));
extern void func_020ee62c(void *);
extern void func_020edf54(void *);

extern unsigned char data_020da13c[];
extern unsigned char data_ov003_0223bc7c[];

void *func_ov003_02220a14(void *obj)
{
    *((void **) obj) = (void *) data_ov003_0223bc7c;
    func_ov003_02223b34((char *) obj + 0x4b20);
    func_02055438((char *) obj + 0x4b10);
    func_02055438((char *) obj + 0x4b00);
    func_02055438((char *) obj + 0x4af0);
    func_02055438((char *) obj + 0x4ae0);
    func_02138c48((char *) obj + 0x49a8, 2, 0x9c, func_02055764);
    func_02138c48((char *) obj + 0x4840, 2, 0x9c, func_02055764);
    func_02138c48((char *) obj + 0x4708, 2, 0x9c, func_02055764);
    func_02138c48((char *) obj + 0x43e8, 5, 0x9c, func_02055764);
    func_02138c48((char *) obj + 0x3068, 0x20, 0x9c, func_02055764);
    func_02138c48((char *) obj + 0x2df0, 4, 0x9c, func_02055764);
    func_02138c48((char *) obj + 0x1590, 0x28, 0x9c, func_02055764);
    func_02138c48((char *) obj + 0x11e8, 6, 0x9c, func_02055764);
    func_02138c48((char *) obj + 0x1014, 3, 0x9c, func_02055764);
    func_02138c48((char *) obj + 0x0c6c, 6, 0x9c, func_02055764);
    func_02138c48((char *) obj + 0x0174, 0x12, 0x9c, func_02055764);
    *((void **) obj) = (void *) data_020da13c;
    func_020ee62c(obj);
    func_020edf54(obj);
    return obj;
}
