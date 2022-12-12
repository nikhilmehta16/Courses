#ifndef __TILES_H__
#define __TILES_H__

// orientations of basic tiles
typedef enum _basicTiles {
	a0,  // [a]
	a1,  // [rotate(a)]
	a2,  // [rotate(rotate((a))]
	a3,  // [rotate(rotate(rotate(a)))]
	b0,  // [b]
	b1,  // [rotate(b)]
	b2,  // [rotate(rotate(b))]
	b3   // [rotate(rotate(rotate(b)))]
} basicTiles;

// printing of basicTiles. Example: basicTileStr[a0] will produce "a0".
extern char *basicTileStr[];

// pattern to represent MxN tiles. 
struct _pattern {
  unsigned int rows;
  unsigned int cols;
  basicTiles **mat;
};
typedef struct _pattern pattern;

// to convert a basic tile, say a0, to a tile pattern {rows=1, cols=1, mat=[a0]}
pattern *makeSingleton(basicTiles tl);

// library functions for the corresponding tile functions
void showTiles(pattern *p);
pattern *rotate(pattern *p);
pattern *concat(pattern *p1, pattern *p2);

#endif /* __TILES_H__ */
