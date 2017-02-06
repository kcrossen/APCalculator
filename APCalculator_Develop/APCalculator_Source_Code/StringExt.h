#define MakeSafeString(NameSafeString, CapacitySafeString) SafeString NameSafeString = { .Capacity = CapacitySafeString, .Characters[CapacitySafeString-1]='\0' }

typedef struct {
    int Capacity;
    char Text[];
} SafeString;

typedef struct {
    int Capacity;
    char Text[101];
} SafeString100;

typedef struct {
    int Capacity;
    char Text[1001];
} SafeString1000;

typedef struct {
    int Capacity;
    char Text[10001];
} SafeString10000;

/* SafeString1000 ss_1000 = { .Capacity = 1000, .Text = "abc" }; */

char* str_trim(char* string_to_trim);

char* str_copy(char* string_to_copy);

char* str_skipchar(char* string_to_skipchar, char skipchar);

char* str_skipspace(char* string_to_skipblank);

char* str_skiptab(char* string_to_skiptab);

int str_counttab(char* string_to_counttab);
