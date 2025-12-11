#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

// --- UI Colors (ANSI Escape Codes) ---
#define COLOR_RESET   "\033[0m"
#define COLOR_RED     "\033[1;31m"
#define COLOR_GREEN   "\033[1;32m"
#define COLOR_YELLOW  "\033[1;33m"
#define COLOR_BLUE    "\033[1;34m"
#define COLOR_CYAN    "\033[1;36m"
#define COLOR_BOLD    "\033[1m"

// --- Constants & Configuration ---
#define MAX_LINE_LENGTH 256
#define DATA_FILENAME "data"

// Static alloc is faster/simpler here. 
// Switch to malloc/linked-list if > 2000 to avoid stack overflow.
#define MAX_ELVES 2000

// --- Domain Models ---
typedef struct {
    char name[MAX_LINE_LENGTH];
    
    // long long required to prevent integer overflow (int is too small).
    long long totalCalories;
} Elf;

// --- Helper Functions ---

void trim_newline(char *str) {
    str[strcspn(str, "\r\n")] = 0;
}

bool is_empty_line(const char *line) {
    return line[0] == '\0';
}

bool is_calorie_count(const char *line) {
    return isdigit(line[0]);
}

// --- Core Logic ---

int compare_elves_descending(const void *a, const void *b) {
    const Elf *elfA = (const Elf *)a;
    const Elf *elfB = (const Elf *)b;
    
    // WARNING: Explicit comparison needed. 
    // Subtraction (b - a) causes overflow when casting long long to int.
    if (elfB->totalCalories > elfA->totalCalories) return 1;
    if (elfB->totalCalories < elfA->totalCalories) return -1;
    return 0;
}

void save_current_elf(Elf *elves, int *count, char *name, long long calories) {
    if (*count >= MAX_ELVES) return; // Bounds check
    
    strcpy(elves[*count].name, name);
    elves[*count].totalCalories = calories;
    (*count)++;
}

int load_elves_from_file(const char *filename, Elf *elves) {
    FILE *file = fopen(filename, "r");
    if (!file) return -1;

    char line[MAX_LINE_LENGTH];
    char currentName[MAX_LINE_LENGTH] = "";
    long long currentCalories = 0;
    int elfCount = 0;
    bool processingElf = false;

    // fgets is safer than fscanf (buffer limits & empty line detection).
    while (fgets(line, sizeof(line), file)) {
        trim_newline(line);

        if (is_empty_line(line)) {
            if (processingElf) {
                save_current_elf(elves, &elfCount, currentName, currentCalories);
                currentCalories = 0; 
                processingElf = false;
            }
            continue;
        }

        if (is_calorie_count(line)) {
            currentCalories += atoll(line);
        } else {
            strcpy(currentName, line);
            processingElf = true;
        }
    }

    // CRITICAL: Handle EOF without newline. Prevents dropping the last elf.
    if (processingElf) {
        save_current_elf(elves, &elfCount, currentName, currentCalories);
    }

    fclose(file);
    return elfCount;
}

void print_podium(Elf *elves, int count) {
    printf(COLOR_BLUE "\n--- COOKIE BATTLE RESULTS ---\n\n" COLOR_RESET);

    if (count > 0) {
        // Le vainqueur en JAUNE (Or)
        printf("🍪 WINNER: " COLOR_YELLOW "%s" COLOR_RESET " with " COLOR_BOLD "%lld" COLOR_RESET " calories!\n", 
               elves[0].name, elves[0].totalCalories);
    }
    
    if (count >= 3) {
        // Les suivants en CYAN (Argenté/Bleuté)
        printf("🥈 RUNNERS UP: " COLOR_CYAN "%s" COLOR_RESET " (%lld) and " COLOR_CYAN "%s" COLOR_RESET " (%lld)\n", 
               elves[1].name, elves[1].totalCalories, 
               elves[2].name, elves[2].totalCalories);
        
        long long top3Total = elves[0].totalCalories + elves[1].totalCalories + elves[2].totalCalories;
        
        // Le total final en VERT (Succès)
        printf("\n🎁 TOTAL POWER (Top 3): " COLOR_GREEN "%lld" COLOR_RESET " calories\n", top3Total);
    }
}

// --- Main Execution ---

int main() {
    Elf elves[MAX_ELVES];
    
    int totalElves = load_elves_from_file(DATA_FILENAME, elves);

    if (totalElves == -1) {
        // Erreur en ROUGE
        fprintf(stderr, COLOR_RED "Error: Could not open file '%s'.\n" COLOR_RESET, DATA_FILENAME);
        return EXIT_FAILURE;
    }

    // Sort is O(N log N). Negligible cost vs readability compared to O(N) scan.
    qsort(elves, totalElves, sizeof(Elf), compare_elves_descending);
    
    print_podium(elves, totalElves);

    return EXIT_SUCCESS;
}