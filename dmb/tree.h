#ifndef DMB_MAP
#define DMB_MAP

typedef struct Map Map;

struct Map {
  int k;
  int v;
  Map *L; 
  Map *R;
};

Map *M_init(int k, int v); 

// *_*
void M_set(Map **m, int k, int v);

int *M_get(Map *m, int k);

#endif
