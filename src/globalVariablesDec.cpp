#include "globalVariables.h"

Rectangle groundMap[60][30] = {};
int currentLevel = village;
int fadeState = FADE_NONE;

float fadeAlpha = 0.0f;
float fadeSpeed = 1.5f;
float fadeHoldTime = 0.1f;
float fadeTimer = 0.0f;