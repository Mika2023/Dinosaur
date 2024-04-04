#pragma once

#define GREEN "\033[32m"
#define ORANGE "\033[33m"
#define BLUE "\033[36m"
#define RESET "\033[0m"

const int birth_age = 4;
const int to_birth = 3;

const int start_grass_count = 40;
const int start_herb_count = 10;
const int start_pred_count = 5;

const int grass_age = 10;
const int grass_spawnrate = 5; //lower is more

const int width = 40;
const int height = 20;

const int herb_age = 40;
const int herb_speed = 1;
const int herb_starving = 10;
const int herb_startstarve = 40;
const int herb_rad = 4;

const int pred_age = 100;
const int pred_speed = 3;
const int pred_starving = 10;
const int pred_startstarve = 50;
const int pred_rad = 6;
