#ifndef _UTIL_STRUCTURE_
#define _UTIL_STRUCTURE_

#define PRINT_BOARD_SIZE 15
#define BOARD_SIZE	15
#define MAX 200
#define NUM_WORDS 100

char board[BOARD_SIZE][BOARD_SIZE];

char bonus_board[BOARD_SIZE][BOARD_SIZE] = {
        {0, 0, 0, 1, 2, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0},
        {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0},
        {1, 2, 0, 0, 1, 0, 1, 0, 0, 0, 2, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2, 0, 0},
        {0, 0, 1, 0, 0, 2, 0, 0, 0, 1, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2, 1},
        {0, 0, 1, 2, 0, 0, 2, 0, 0, 0, 1, 0, 2, 0, 1},
        {0, 1, 0, 0, 1, 0, 0, 2, 0, 0, 0, 1, 0, 1, 0},
        {0, 1, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 2, 0, 0, 0},
        {0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 0},
        {0, 0, 2, 1, 0, 0, 0, 0, 0, 0, 1, 0, 2, 0, 0},
        {0, 0, 1, 1, 0, 1, 0, 0, 0, 2, 0, 0, 0, 0, 0}};

char words[][NUM_WORDS] = {
	"AIRPLANE",
	"COMMUNITY",
	"INCLUDE",
	"INFORMATION",
	"SOCIAL",
	"HEALTH",
	"PERSON",
	"SCHOOL",
	"HISTORY",
	"PARTY",
	"OPEN",
	"REASON",
	"TEACHER",
	"OFFER",
	"EDUCATION",
	"REMEMBER",
	"LEADER",
	"DECISION",
	"REPORT",
	"DIRECTOR",
	"PAPER",
	"CENTER",
	"PROJECT",
	"UNIVERSITY",
	"MUSIC",
	"TABLE",
	"FACE",
	"DATA",
	"PHONE",
	"PRODUCT",
	"WALL",
	"WORKER",
	"MOVIE",
	"OPEN",
	"STEP",
	"FILM",
	"CENTURY",
	"POINT",
	"WINDOW",
	"BROTHER",
	"SUMMER",
	"PLANT",
	"PLACE",
	"POPULATION",
	"ECONOMY",
	"FIRE",
	"FUTURE",
	"INCREASE",
	"SECURITY",
	"DEAL",
	"BEHAVIOUR",
	"FIGHT",
	"GOAL",
	"BED",
	"ORDER",
	"PLAN",
	"NATURE",
	"COLOR",
	"STORE",
	"LANGUAGE",
	"ARTICLE",
	"SEVEN",
	"ARTIST",
	"EIGHT",
	"ONE",
	"HAPPY",
	"CAT",
	"DOG",
	"FISH",
	"SIGN",
	"CUP",
	"WONDER",
	"TRAINING",
	"MACHINE",
	"ELECTION",
	"MESSAGE",
	"ANALYSIS",
	"NAME",
	"FAIL",
	"GLASS",
	"ANSWER",
	"SKILL",
	"FINANCIAL",
	"SORT",
	"ACT",
	"TEN",
	"KNOWLEDGE",
	"BLUE",
	"LITTLE",
	"DARK",
	"LIGHT",
	"STUDY",
	"SCIENCE",
	"GREEN",
	"MEMORY",
	"EXPERT",
	"SPRING",
	"RADIO",
	"MANAGEMENT",
	"THEORY"
};

#endif