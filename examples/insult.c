/* Insult.c

   This is a version of the famous CS 107 random sentence
   generator.  I wrote a program that reads a grammar definition
   file and writes a C file containing that grammar as hard code
   static C strings.  Thus the majority of the code below in
   machine generated and totally unreadable.  The arrays created
   are specially designed to make generating the sentences as
   easy as possible.

   Originally by Greg Hutchins, March 1998.
   Modified by Ben Pfaff for Pintos, Sept 2004. */
char *start[] =
  { "You", "1", "5", ".", "May", "13", ".", "With", "the", "19", "of", "18",
",", "may", "13", "."
};
char startLoc[] = { 3, 0, 4, 7, 16 };
char *adj[] = { "3", "4", "2", ",", "1" };
char adjLoc[] = { 3, 0, 1, 2, 5 };
char *adj3[] = { "3", "4" };
char adj3Loc[] = { 2, 0, 1, 2 };
char *adj1[] =
  { "lame", "dried", "up", "par-broiled", "bloated", "half-baked", "spiteful",
"egotistical", "ungrateful", "stupid", "moronic", "fat", "ugly", "puny", "pitiful",
"insignificant", "blithering", "repulsive", "worthless", "blundering", "retarded",
"useless", "obnoxious", "low-budget", "assinine", "neurotic", "subhuman", "crochety",
"indescribable", "contemptible", "unspeakable", "sick", "lazy", "good-for-nothing",
"slutty", "mentally-deficient", "creepy", "sloppy", "dismal", "pompous", "pathetic",
"friendless", "revolting", "slovenly", "cantankerous", "uncultured", "insufferable",
"gross", "unkempt", "defective", "crumby"
};
char adj1Loc[] =
  { 50, 0, 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42,
43, 44, 45, 46, 47, 48, 49, 50, 51 };
char *adj2[] =
  { "putrefied", "festering", "funky", "moldy", "leprous", "curdled", "fetid",
"slimy", "crusty", "sweaty", "damp", "deranged", "smelly", "stenchy", "malignant",
"noxious", "grimy", "reeky", "nasty", "mutilated", "sloppy", "gruesome", "grisly",
"sloshy", "wormy", "mealy", "spoiled", "contaminated", "rancid", "musty",
"fly-covered", "moth-eaten", "decaying", "decomposed", "freeze-dried", "defective",
"petrified", "rotting", "scabrous", "hirsute"
};
char adj2Loc[] =
  { 40, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40 };
char *name[] =
  { "10", ",", "bad", "excuse", "for", "6", ",", "6", "for", "brains", ",",
"4", "11", "8", "for", "brains", "offspring", "of", "a", "motherless", "10", "7", "6",
"7", "4", "11", "8"
};
char nameLoc[] = { 7, 0, 1, 6, 10, 16, 21, 23, 27 };
char *stuff[] =
  { "shit", "toe", "jam", "filth", "puss", "earwax", "leaf", "clippings",
"bat", "guano", "mucus", "fungus", "mung", "refuse", "earwax", "spittoon", "spittle",
"phlegm"
};
char stuffLoc[] = { 14, 0, 1, 3, 4, 5, 6, 8, 10, 11, 12, 13, 14, 15, 17, 18 };
char *noun_and_prep[] =
  { "bit", "of", "piece", "of", "vat", "of", "lump", "of", "crock", "of",
"ball", "of", "tub", "of", "load", "of", "bucket", "of", "mound", "of", "glob", "of", "bag",
"of", "heap", "of", "mountain", "of", "load", "of", "barrel", "of", "sack", "of", "blob", "of",
"pile", "of", "truckload", "of", "vat", "of"
};
char noun_and_prepLoc[] =
  { 21, 0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36,
38, 40, 42 };
char *organics[] =
  { "droppings", "mung", "zits", "puckies", "tumors", "cysts", "tumors",
"livers", "froth", "parts", "scabs", "guts", "entrails", "blubber", "carcuses", "gizards",
"9"
};
char organicsLoc[] =
  { 17, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17 };
char *body_parts[] =
  { "kidneys", "genitals", "buttocks", "earlobes", "innards", "feet"
};
char body_partsLoc[] = { 6, 0, 1, 2, 3, 4, 5, 6 };
char *noun[] =
  { "pop", "tart", "warthog", "twinkie", "barnacle", "fondue", "pot",
"cretin", "fuckwad", "moron", "ass", "neanderthal", "nincompoop", "simpleton", "11"
};
char nounLoc[] = { 13, 0, 2, 3, 4, 5, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
char *animal[] =
  { "donkey", "llama", "dingo", "lizard", "gekko", "lemur", "moose", "camel",
"goat", "eel"
};
char animalLoc[] = { 10, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
char *good_verb[] =
  { "love", "cuddle", "fondle", "adore", "smooch", "hug", "caress", "worship",
"look", "at", "touch"
};
char good_verbLoc[] = { 10, 0, 1, 2, 3, 4, 5, 6, 7, 8, 10, 11 };
char *curse[] =
  { "14", "20", "23", "14", "17", "20", "23", "14", "find", "your", "9",
"suddenly", "delectable", "14", "and", "14", "seek", "a", "battleground", "23"
};
char curseLoc[] = { 4, 0, 3, 7, 13, 20 };
char *afflictors[] =
  { "15", "21", "15", "21", "15", "21", "15", "21", "a", "22", "Rush",
"Limbaugh", "the", "hosts", "of", "Hades"
};
char afflictorsLoc[] = { 6, 0, 2, 4, 6, 8, 12, 16 };
char *quantity[] =
  { "a", "4", "hoard", "of", "a", "4", "pack", "of", "a", "truckload", "of",
"a", "swarm", "of", "many", "an", "army", "of", "a", "4", "heard", "of", "a", "4",
"platoon", "of", "a", "4", "and", "4", "group", "of", "16"
};
char quantityLoc[] = { 10, 0, 4, 8, 11, 14, 15, 18, 22, 26, 32, 33 };
char *numbers[] =
  { "a", "thousand", "three", "million", "ninty-nine", "nine-hundred,",
"ninty-nine", "forty-two", "a", "gazillion", "sixty-eight", "times", "thirty-three"
};
char numbersLoc[] = { 7, 0, 2, 4, 5, 7, 8, 10, 13 };
char *adv[] =
  { "viciously", "manicly", "merrily", "happily", ",", "with", "the", "19",
"of", "18", ",", "gleefully", ",", "with", "much", "ritualistic", "celebration", ",",
"franticly"
};
char advLoc[] = { 8, 0, 1, 2, 3, 4, 11, 12, 18, 19 };
char *metaphor[] =
  { "an", "irate", "manticore", "Thor's", "belch", "Alah's", "fist", "16",
"titans", "a", "particularly", "vicious", "she-bear", "in", "the", "midst", "of", "her",
"menstrual", "cycle", "a", "pissed-off", "Jabberwock"
};
char metaphorLoc[] = { 6, 0, 3, 5, 7, 9, 20, 23 };
char *force[] = { "force", "fury", "power", "rage" };
char forceLoc[] = { 4, 0, 1, 2, 3, 4 };
char *bad_action[] =
  { "spit", "shimmy", "slobber", "find", "refuge", "find", "shelter", "dance",
"retch", "vomit", "defecate", "erect", "a", "strip", "mall", "build", "a", "26", "have", "a",
"religious", "experience", "discharge", "bodily", "waste", "fart", "dance", "drool",
"lambada", "spill", "16", "rusty", "tacks", "bite", "you", "sneeze", "sing", "16",
"campfire", "songs", "smite", "you", "16", "times", "construct", "a", "new", "home", "throw",
"a", "party", "procreate"
};
char bad_actionLoc[] =
  { 25, 0, 1, 2, 3, 5, 7, 8, 9, 10, 11, 15, 18, 22, 25, 26, 27, 28, 29, 33,
35, 36, 40, 44, 48, 51, 52 };
char *beasties[] =
  { "yaks", "22", "maggots", "22", "cockroaches", "stinging", "scorpions",
"fleas", "22", "weasels", "22", "gnats", "South", "American", "killer", "bees", "spiders",
"4", "monkeys", "22", "wiener-dogs", "22", "rats", "22", "wolverines", "4", ",", "22",
"pit-fiends"
};
char beastiesLoc[] =
  { 14, 0, 1, 3, 5, 7, 8, 10, 12, 16, 17, 19, 21, 23, 25, 29 };
char *condition[] =
  { "frothing", "manic", "crazed", "plague-ridden", "disease-carrying",
"biting", "rabid", "blood-thirsty", "ravaging", "slavering"
};
char conditionLoc[] = { 10, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
char *place[] =
  { "in", "24", "25", "upon", "your", "mother's", "grave", "on", "24", "best",
"rug", "in", "the", "26", "you", "call", "home", "upon", "your", "heinie"
};
char placeLoc[] = { 5, 0, 3, 7, 11, 17, 20 };
char *relation[] =
  { "your", "your", "your", "your", "father's", "your", "mother's", "your",
"grandma's"
};
char relationLoc[] = { 6, 0, 1, 2, 3, 5, 7, 9 };
char *in_something[] =
  { "entrails", "anal", "cavity", "shoes", "house", "pantry", "general",
"direction", "pants", "bed"
};
char in_somethingLoc[] = { 8, 0, 1, 3, 4, 5, 6, 8, 9, 10 };
char *bad_place[] =
  { "rat", "hole", "sewer", "toxic", "dump", "oil", "refinery", "landfill",
"porto-pottie"
};
char bad_placeLoc[] = { 6, 0, 2, 3, 5, 7, 8, 9 };
char **daGrammar[27];
char *daGLoc[27];

static void
init_grammar (void)
{
  daGrammar[0] = start;
  daGLoc[0] = startLoc;
  daGrammar[1] = adj;
  daGLoc[1] = adjLoc;
  daGrammar[2] = adj3;
  daGLoc[2] = adj3Loc;
  daGrammar[3] = adj1;
  daGLoc[3] = adj1Loc;
  daGrammar[4] = adj2;
  daGLoc[4] = adj2Loc;
  daGrammar[5] = name;
  daGLoc[5] = nameLoc;
  daGrammar[6] = stuff;
  daGLoc[6] = stuffLoc;
  daGrammar[7] = noun_and_prep;
  daGLoc[7] = noun_and_prepLoc;
  daGrammar[8] = organics;
  daGLoc[8] = organicsLoc;
  daGrammar[9] = body_parts;
  daGLoc[9] = body_partsLoc;
  daGrammar[10] = noun;
  daGLoc[10] = nounLoc;
  daGrammar[11] = animal;
  daGLoc[11] = animalLoc;
  daGrammar[12] = good_verb;
  daGLoc[12] = good_verbLoc;
  daGrammar[13] = curse;
  daGLoc[13] = curseLoc;
  daGrammar[14] = afflictors;
  daGLoc[14] = afflictorsLoc;
  daGrammar[15] = quantity;
  daGLoc[15] = quantityLoc;
  daGrammar[16] = numbers;
  daGLoc[16] = numbersLoc;
  daGrammar[17] = adv;
  daGLoc[17] = advLoc;
  daGrammar[18] = metaphor;
  daGLoc[18] = metaphorLoc;
  daGrammar[19] = force;
  daGLoc[19] = forceLoc;
  daGrammar[20] = bad_action;
  daGLoc[20] = bad_actionLoc;
  daGrammar[21] = beasties;
  daGLoc[21] = beastiesLoc;
  daGrammar[22] = condition;
  daGLoc[22] = conditionLoc;
  daGrammar[23] = place;
  daGLoc[23] = placeLoc;
  daGrammar[24] = relation;
  daGLoc[24] = relationLoc;
  daGrammar[25] = in_something;
  daGLoc[25] = in_somethingLoc;
  daGrammar[26] = bad_place;
  daGLoc[26] = bad_placeLoc;
}

#include <ctype.h>
#include <debug.h>
#include <random.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syscall.h>

void expand (int num, char **grammar[], char *location[], int handle);

static void
usage (int ret_code, const char *message, ...) PRINTF_FORMAT (2, 3);

static void
usage (int ret_code, const char *message, ...)
{
  va_list args;

  if (message != NULL) 
    {
      va_start (args, message);
      vprintf (message, args);
      va_end (args);
    }
  
  printf ("\n"
          "Usage: insult [OPTION]...\n"
          "Prints random insults to screen.\n\n"
          "  -h:               this help message\n"
          "  -s <integer>:     set the random seed (default 4951)\n"
          "  -n <integer>:     choose number of insults (default 4)\n"
          "  -f <file>:        redirect output to <file>\n");

  exit (ret_code);
}

int
main (int argc, char *argv[])
{
  int sentence_cnt, new_seed, i, file_flag, sent_flag, seed_flag;
  int handle;
  
  new_seed = 4951;
  sentence_cnt = 4;
  file_flag = 0;
  seed_flag = 0;
  sent_flag = 0;
  handle = STDOUT_FILENO;

  for (i = 1; i < argc; i++)
    {
      if (strcmp (argv[1], "-h") == 0)
        usage (0, NULL);
      else if (strcmp (argv[i], "-s") == 0)
	{
	  if (seed_flag++)
	    usage (-1, "Can't have more than one seed");
	  if (++i >= argc)
	    usage (-1, "Missing value for -s");
	  new_seed = atoi (argv[i]);
	}
      else if (strcmp (argv[i], "-n") == 0)
	{
	  if (sent_flag++)
	    usage (-1, "Can't have more than one sentence option");
	  if (++i >= argc)
	    usage (-1, "Missing value for -n");
	  sentence_cnt = atoi (argv[i]);
	  if (sentence_cnt < 1)
	    usage (-1, "Must have at least one sentence");
	}
      else if (strcmp (argv[i], "-f") == 0)
	{
	  if (file_flag++)
	    usage (-1, "Can't have more than one output file");
	  if (++i >= argc)
	    usage (-1, "Missing value for -f");

          /* Because files have fixed length in the basic Pintos
             file system, the 0 argument means that this option
             will not be useful until project 4 is
             implemented. */
	  create (argv[i], 0);
	  handle = open (argv[i]);
          if (handle < 0)
            {
              printf ("%s: open failed\n", argv[i]);
              return EXIT_FAILURE;
            }
	}
      else
        usage (-1, "Unrecognized flag");
    }

  init_grammar ();

  random_init (new_seed);
  hprintf (handle, "\n");

  for (i = 0; i < sentence_cnt; i++)
    {
      hprintf (handle, "\n");
      expand (0, daGrammar, daGLoc, handle);
      hprintf (handle, "\n\n");
    }
  
  if (file_flag)
    close (handle);

  return EXIT_SUCCESS;
}

void
expand (int num, char **grammar[], char *location[], int handle)
{
  char *word;
  int i, which, listStart, listEnd;

  which = random_ulong () % location[num][0] + 1;
  listStart = location[num][which];
  listEnd = location[num][which + 1];
  for (i = listStart; i < listEnd; i++)
    {
      word = grammar[num][i];
      if (!isdigit (*word))
	{
	  if (!ispunct (*word))
            hprintf (handle, " ");
          hprintf (handle, "%s", word);
	}
      else
	expand (atoi (word), grammar, location, handle);
    }

}
