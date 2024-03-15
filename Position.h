#pragma once
struct Position {
	int x;
	int y;
};

enum content {
	empty,
	gr,
	herbivorous,
	predator
};

struct WorldStruct
{
	int index;
	content cont;
};