#if !defined(MKFUNC_H)
#define MKFUNC_H

void mkfile(const char *fname, const char *equation);
void compile(const char *fname);
void mkcsv(const char *fname, double xmin, double xmax, int xnum, double ymin, double ymax, int ynum);
void mkfunc(const char *fname, const char *equation, double xmin, double xmax, int xnum, double ymin, double ymax, int ynum);

#endif /* MKFUNC_H */
