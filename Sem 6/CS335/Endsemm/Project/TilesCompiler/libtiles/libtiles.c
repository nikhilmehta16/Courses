#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<tiles.h>

char *basicTileStr[]  = {"a0", "a1", "a2", "a3", "b0", "b1", "b2", "b3"};

pattern *makeSingleton(basicTiles tl) {
    pattern *pat = (pattern*) malloc(sizeof(pattern));
    pat->rows = pat->cols = 1;
    pat->mat = (basicTiles**)malloc(sizeof(basicTiles*));
    pat->mat[0] = (basicTiles*)malloc(sizeof(basicTiles));
    pat->mat[0][0] = tl;
    return pat;
}

void showTiles(pattern *p) {
	FILE *fp = fopen("/dev/tty", "w");
	fprintf(fp, "%d,%d\n", p->rows, p->cols);
	for (int i = 0; i < p->rows; ++i) {
		fprintf(fp, "[");
		for (int j = 0; j < p->cols; ++j) {
			char*sep = j == p->cols-1 ? "" : ",";
			fprintf(fp, "%s%s", basicTileStr[p->mat[i][j]], sep);
		}
		fprintf(fp, "]\n");
	}
	fclose(fp);
	return;
}

pattern *concat(pattern *left, pattern *right) {
	if (left->rows != right->rows) {
		fprintf(stderr, "CONCAT Error: Incompatible tiles for concatenation\n");
		exit(-1);
	}
	pattern* res = (pattern*)malloc(sizeof(pattern));
	res->rows = left->rows;
	res->cols = left->cols + right->cols;
	res->mat = (basicTiles**)malloc(res->rows*sizeof(basicTiles*));
	for (int i = 0; i < res->rows; ++i) {
		res->mat[i] = (basicTiles*)malloc(res->cols*sizeof(basicTiles));
		for (int j = 0; j < left->cols; ++j) {
			res->mat[i][j] = left->mat[i][j]; 
		}
		for (int j = 0; j < right->cols; ++j) {
			int jr = left->cols + j;
			res->mat[i][jr] = right->mat[i][j]; 
		}
	}
	return res;
}

// turn a basic tile by 90 deg clockwise.
static basicTiles turn(basicTiles tl) {
	switch (tl) {
		case a0: return a1;
		case a1: return a2;
		case a2: return a3;
		case a3: return a0;
		case b0: return b1;
		case b1: return b2;
		case b2: return b3;
		case b3: return b0;
		default: assert(0 && "WHY?");
	}
}
// 90 deg rotation =>   result[i][j] --> turn(t[n-j-1][i])
pattern *rotate(pattern *t) {
	pattern* res = (pattern*)malloc(sizeof(pattern));
	res->rows = t->cols;
	res->cols = t->rows;
	res->mat = (basicTiles**)malloc(res->rows*sizeof(basicTiles*));
	for (int i = 0; i < res->rows; ++i) {
		res->mat[i] = (basicTiles*)malloc(res->cols*sizeof(basicTiles));
		for (int j = 0; j < res->cols; ++j) {
			res->mat[i][j] = turn(t->mat[t->rows-j-1][i]); 
		}
	}
	return res;
}

