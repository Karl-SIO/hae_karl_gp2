#pragma once
/*
struct Vec3 {
	float x;
	float y;
	float z;
};
*/
/*/
typedef struct Vec3 {
	float x;
	float y;
	float z;
} VEC3;

struct LIST;
typedef struct List {
	LIST p;
} LIST;
*/

struct MonEpee; //{}

struct MaBotte {
	MonEpee * x;
};

struct MonEpee {
	MaBotte * x;
};

typedef int MONINT;
typedef int IDENTIFIANT;

/*
class Player 
{
	Id KeyId;
	Id PasseportId;
};
*/