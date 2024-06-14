/*****************************************************************
//
//  NAMES:       Adam Graham
//               Shayde Tamura
//
//  ASSIGNMENT:  2
//
//  CLASS:       ICS 311
//
//  INSTRUCTOR:  Brook Conner
//
//  DATE:        June 12, 2024
//
//  FILE:        saying.h
//
//  DESCRIPTION:
//   Header file for the Hawaiian and English sayings with their
//   associated explanations.
//
****************************************************************/

#include <wchar.h>

struct Saying
{
    wchar_t hawaiian[256];
    char english[256];
    char hawaiianExplanation[256];
    char englishExplanation[256];
};