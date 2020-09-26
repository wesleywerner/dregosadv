

!---------------------------------------------------------------------------
!   07/2020
!   This file is included with Dr Ego's Adventure and modified from the
!   original to fit better into the story. 
!   My thanks to E. Short for her contribution in this regard!
!
!   To customize the help for your story:
!     1. Edit the main help options in the HelpMenu routine.
!     2. Edit the list of verbs available in the StandardVerbs routine.
!     3. Edit the wording in the AboutSub routine.
!     4. Add new help commands to the HelpSub routine.
!
!---------------------------------------------------------------------------
!	HelpRoutines.h, by Emily Short (emshort@mindspring.com) 
!	Version 1.0 
!	8/16/02 
!
!	Being a file of straightforward routines that will make your game print
!	wodges and wodges of text about IF playing. 
!	
!	Some portions based on paraphrase of instructional text by 
!	Stephen Granade.
!---------------------------------------------------------------------------
!
!	RIGHTS:
!	
!	This library file may be treated as public domain.  It may be
!	used in source with or without credit to the original author.  It may be
!	modified at the user's discretion.  It may be freely redistributed.
!	The textual content of the routines may be lifted from their context
!	and reused elsewhere.
!
!
!	INSTALLATION: 
!
!	Include "HelpRoutines" in your gamefile.
!
!
!	CONTENTS:
!
!	-- Three basic formatting routines for doing bold and italic text
!		and for awaiting a keypress.  (The only reason to define these 
!		is to provide z-code/Glulx flexibility.)
!
!	-- LongIntro.  A description of IF, which prints both of
!		-- BasicBrief.  A quick description of IF in the abstract
!		-- BasicIntro.  A somewhat longer description of same, discuss
!
!	-- ExplainPrompt.  What a prompt is.
!	-- StartingInstructions.  Suggests that the player look, examine items,
!			and check his inventory.
!	-- StuckInstructions.  A list of tips for a player in trouble
!
!	-- AllCommunication.  Prints all of the following:
!		-- Communication.  Basic instructions on how to form valid commands.
!		-- OnMovement
!		-- OnObjects 
!		-- OnNPCs, which will also call one of
!			-- AskTellNPC
!			-- MenuNPC (Define NPC_MENU before including this file)
!			-- TalkToNPC (Define NPC_TALKTO before including this file)
!			-- TopicMenuNPC (Define NPC_TOPIC before including this file) 
!		-- MetaCommands.  Introduces SAVE, QUIT, RESTART, RESTORE, UNDO.
!
!	-- StandardVerbs.  A list of standard verbs.  Self-adjusting to reflect
!	    the instructions about NPCS; it will list SCORE only if you have a MAX_SCORE 
!		greater than 0, and the OBJECTS/PLACES commands only if you have not defined
!		NO_PLACES.
!	-- Abbreviations.  A list of abbreviations and their meanings.
!
!	-- OnlineHelp.  How to find online IF manuals.
!	-- MoreGames.  How to find more IF. 
!
!	SEE ALSO: 
!		-- SampleTranscript.h: contains several sample transcripts formatted
!			for inclusion in IF games.
!
!	CAVEAT
!
!	Note that in some cases this material may be incorrect for your game.  
!	You are advised to read the resulting text and determine whether it suits 
!	your ends. 
!
!---------------------------------------------------------------------------


system_file;


!---------------------------------------------------------------------------
! Special effects -- bold-texting and pauses for display purposes
!--------------------------------------------------------------------------- 

#ifdef TARGET_GLULX;
[ ES_Pause i; 
	i = KeyCharPrimitive();  
	if (i=='q') rtrue;
	rfalse; 
];
#ifnot;
[ ES_Pause i;
	@read_char 1 i;
	if (i == 'q') rtrue;
	rfalse; 
];
#endif;

#ifdef TARGET_GLULX;
[ ESB str;	! print something in bold 
	if (str==0) rfalse;
	glk_set_style(style_Input);
	print (string) str; 
	glk_set_style(style_Normal);
	rtrue;
];
#ifnot;
[ ESB str;	! print something in bold 
	if (str==0) rfalse;
	style bold;
	print (string) str; 
	style roman;
	rtrue;
];
#endif;

#ifdef TARGET_GLULX;
[ ESI str;	! print something in italics 
	if (str==0) rfalse;
	glk_set_style(style_Emphasized);
	print (string) str; 
	glk_set_style(style_Normal);
	rtrue;
];
#ifnot;
[ ESI str;	! print something in italics 
	if (str==0) rfalse;
	style underline;
	print (string) str; 
	style roman;
	rtrue;
];
#endif;



!---------------------------------------------------------------------------
! Help Verb
!--------------------------------------------------------------------------- 

! The first time help is displayed a short introductory text is automatically
! printed, for the sake of players new to IF.
Global auto_print_help_intro = true;

! The HELP verb gives the player instructions on how to play.
[ HelpSub help_topic;

    ! Reposition the word marker
    wn = consult_from;

    ! Read the first word in the topic
    help_topic = NextWord();
    
    ! if a help topic is specified then automatically omit the introductory help.
    if (help_topic) auto_print_help_intro = false;
    
    ! Read words until none are left or the first word is switched.
    ! The while-loop ensures that HELP ME WITH FOO, and HELP FOO, both work equally well.
    while (help_topic) {
        switch (help_topic) {
            'about', 'credits':
                AboutSub();
                return;
            'basic', 'basics': 
                Communication();
                StartingInstructions();
            'commands':
                GameCommands();
            'go', 'going', 'travel':
                OnMovement();
            'verb', 'verbs': 
                StandardVerbs(); 
            'thing', 'things', 'objects':
                OnObjects();
            'npc', 'character', 'characters':
                !OnNPCs();
                TopicMenuNPC();
            'stuck', 'hint':
                StuckInstructions();
            'abbreviations', 'ab':
                Abbreviations();
            'if':
                BasicIntro();
            'save', 'restore', 'score', 'full', 'restart', 'quit':
                MetaCommands();
            'talking':
                AskTellNPC();
            default:
                SpecificVerbHelp(help_topic);
        }
        help_topic = NextWord();
    }

    ! Automatically print BASIC help.
    if (auto_print_help_intro) {
        BasicBrief();
        auto_print_help_intro = false;
        print "^^";
    }
    
    HelpMenu();
    
];
! The meta keyword on the verb makes this a Group 1 action - no turn is actioned.
Verb meta 'help'    *                               -> Help
                    * topic                         -> Help;

!---------------------------------------------------------------------------
! Menu
!--------------------------------------------------------------------------- 

[ AboutSub;
    print (ESB) "ABOUT^";
    print "I began writing this story in April 2020.
    I was watching the Indiana Jones films at the time, and drew
    inspiration from the plucky protagonist.
    ^^
    This was also a time of adventure and upheaval for me.
    I moved to another country earlier in the year, and just like this story,
    I faced challenges I had to solve and overcome.
    ^^
    I also wanted to learn a new interactive fiction authoring system.
    Having written stories in Inform 7 and Quest, I wanted to try a system
    that uses more traditional programming paradigms.
    In the end I chose to write this story in Inform 6.
    ^^
    see CREDITS.
    ^";
    
];

[ CreditsSub;
    print (ESB) "^^CREDITS^";
    print "My thanks to Andrew Schultz, Durafen and Jason Lautzenheiser for 
    testing this story. Your bug hunting and grammar feedback was invaluable.
    Additional thanks to Graham Nelson for creating Inform, and
    Emily Short for putting HelpRoutines.h into the public domain.
    Finally I want to thank you, the player, for coming on this adventure
    with me.
    ^";
];

[ HelpMenu;
	print "Type HELP followed by one of these words to learn more:^";
    
#ifdef TARGET_GLULX;
	glk_set_style(style_Preformatted);
#ifnot;	
	font off;
#endif;

	print "BASICS   ";
	print "GOING    ";
    print "THINGS   ";
	print "VERBS    ";
    print "TALKING  ";
    print "^";
    
	print "SAVE     ";
    print "RESTORE  ";
    print "ABOUT    ";
    print "SCORE    ";
    print "^";
    
    print "IF       ";
    print "STUCK    ";
	print "ABBREVIATIONS (AB)";
	
	print "^";
	
#ifdef TARGET_GLULX;
	glk_set_style(style_Normal);
#ifnot;	
	font on;
#endif;
];

!---------------------------------------------------------------------------
! Specific Verb Help
! Verb help should follow this format:
! 1. fixed-width font of one or more usage examples
!    each line prefixed by two spaces.
! 2. display font of description text.
! 3. should not end with a new line.
! 4. examples should use real world objects, not 'noun' or 'object'.
!--------------------------------------------------------------------------- 

[ SpecificVerbHelp the_verb;
    switch (the_verb) {
        'north', 'south', 'east', 'west',
        'n', 's', 'e', 'w', 'ne', 'nw', 'se', 'sw':
            font off;
            print "  go north^";
            print "  east^";
            print "  sw^";
            font on;
            new_line;
            print "Moves your character in the given direction, provided there
            is an exit that way.  Exits are listed when you LOOK around.";
        'ask', 'tell', 'answer', 'say', 'show', 'give':
            font off;
            print "  ask the butler about the first course^";
            print "  ask the butler for the menu^";
            print "  tell the butler about the mess in the conservatory^";
            print "  answer yes^";
            print "  say yes (alternative form to answer)^";
            print "  show the treasure map to the pirate^";
            print "  give the magic flute to the piper^";
            font on;
            new_line;
            print "These verbs interact with other characters.  
            Asking for a thing simply instructs the other person to give you the
            thing, whether they comply is another matter.  
            Sometimes you need to bribe a character by giving them something
            they want first.  
            Showing an item to a character can also elicit a response.";
        'burn', 'light':
            font off;
            print "  light the candle with the blowtorch^";
            print "  burn the pyre with the Molotov cocktail^";
            font on;
            new_line;
            print "Sets something alight using a flame, which may be a 
            matchbook, a zippo lighter or even a piece of fire-making flint.
            BURN and LIGHT are synonyms.";
        'climb':
            font off;
            print "  climb the fig tree^";
            font on;
            new_line;
            print "Ascends climbable objects: ladders, ropes and jungle gyms.  
            Because English is nuanced you can also climb stairs, although this
            is a different action (GOing UP), some stories allow you to do this 
            -- If this fails, try GO UP to use stairs instead.";
        'dig':
            font off;
            print "  dig in the ground^";
            print "  dig in the garden with the spade^";
            font on;
            new_line;
            print "Makes you dig using a tool that you are carrying.  
            Some stories allow you to dig without a tool, simply omit the
            tool name.";
        'consult', 'read', 'reading', 'research':
            font off;
            print "  consult the book about roman history^";
            print "  look up moon phases in the almanac^";
            print "  read about hallucinations in the medical journal^";
            font on;
            new_line;
            print "Reads about a topic in a book, or other reading 
            material that you are carrying.  Newspapers, almanacs and 
            recipe books are other examples of reading material.  Alternative 
            ways to read include: LOOK UP and READ ABOUT.";
        'cut':
            font off;
            print "  cut the paper with the scissors^";
            print "  cut the rope with the axe^";
            font on;
            new_line;
            print "Some stories need you to cut an item to progress the plot, 
            this verb allows you to do that, simply and succinct.";
        'down', 'up':
            font off;
            print "  go up (when there are stairs)^";
            print "  go down (when hanging from a rope)^";
            print "  down (when standing on a bar counter)^";
            font on;
            new_line;
            print "UP and DOWN are treated as directions, you can GO UP if there
            is a way heading upward: stairs or hills for example.  
            Generally when wanting to ascend a climbable thing like ladders or
            ropes, you should use the CLIMB verb.";
        'drop':
            font off;
            print "  drop the hot potato.^";
            print "  drop all (everything being carried).^";
            font on;
            new_line;
            print "Drop places something you are carrying on the ground. If you
            instead want to place the thing on top of a surface, or inside a 
            container, use the PUT verb instead.";
        'empty':
            font off;
            print "  empty the rucksack^";
            print "  empty the rucksack on the table^";
            font on;
            new_line;
            print "Empties a container of all items and drops them on the 
            ground, or onto another surface. You must be holding the container.  
            If you need to move items from one container to another, 
            see TRANSFER instead.";
        'enter':
            font off;
            print "  enter the small red car^";
            print "  enter the ancient temple^";
            font on;
            new_line;
            print "Entering things is another form of movement when it makes
            grammatical sense - cars, pillow fortresses or walk-in showers
            are examples of places you can enter.  Usually if the story does
            not mention a specific direction of a place, you can try ENTER it.";
        'examine':
            font off;
            print "  examine the ming vase^";
            print "  examine self^";
            print "  x the tomato plant^";
            font on;
            new_line;
            print "";
            print "Describes an item in more detail.  This verb is important
            in any IF story, as examining an item can give you clues to
            how the item can be used, or reveal some detail to help progress
            the story.  
            For brevity this verb can be shortened to X.";
        'exit':
            font off;
            print "  exit (when inside the hovercraft)^";
            print "  exit the speedboat^";
            font on;
            new_line;
            print "Get out of something: a car, a boat and a phone booth.  
            When your character is on top of something (ladder, chair or 
            perhaps a bar counter), type GET OFF instead of exiting.";
        'in', 'out':
            font off;
            print "  go in^";
            print "  out^";
            font on;
            new_line;
            print "Moves into another location or structure (if present), 
            depending on how the story is written. For example
            standing near a tent may allow you to GO IN to enter it, and
            GO OUT to leave it.  ";
        'inventory':
            font off;
            print "  take inventory^";
            print "  i (abbreviated form)^";
            font on;
            new_line;
            print "Lists everything your character is carrying.  
            For brevity you can only type the first letter, ~i~.";
        'lock', 'unlock':
            font off;
            print "  unlock the iron gate with the key^";
            print "  lock the medicine cabinet with the key^";
            font on;
            new_line;
            print "Allows you to manipulate any locking mechanism: Doors, 
            padlocks, electronic keycard system, anything the story deems a 
            lock.  If you are carrying a single key, the story may let you omit
            which key to use.";
        'look': 
            font off;
            print "  look^";
            print "  l (abbreviated form)^";
            print "  look [up] / [north] / [se] / [down]^";
            print "  look under the carpet^";
            font on;
            new_line;
            print "When used alone, LOOK describes what you see around you.  
            When given a compass direction, you describe what you see that way.  
            Looking under things may reveal something hidden.  See SEARCH.";
        'open', 'close':
            font off;
            print "  open the door^";
            print "  close the toy chest^";
            font on;
            new_line;
            print "Opens and closes doors, windows and containers.";
        'pull', 'push':
            font off;
            print "  push the cupboard^";
            print "  pull the silk thread^";
            font on;
            new_line;
            print "Push and pull acts on a variety of items and is a very
            specific action to each story.  Generally you won't be able to 
            push or pull every little thing in the world, but this verb has
            a place in IF puzzle solving --  Like pushing a heavy cupboard out
            the way to reveal a hidden passage, or to push a swing on the 
            playground, or to push the fire alarm button.  
            Generally in IF you don't say which direction to PUSH in, but you
            can if the story requires it -- PULL on the other hand never needs a
            direction.";
        'put':
            font off;
            print "  put the vase on the pedestal^";
            print "  put the melon in the blender^";
            font on;
            new_line;
            print "Places things onto a surface (like a table), or into 
            containers (like a bucket). If you want to put an item on
            the ground, DROP it instead.";
        'remove':
            font off;
            print "  remove the pearl necklace^";
            print "  remove the mango from the crate^";
            font on;
            new_line;
            print "Takes items out of containers, or disrobes a worn garment or
            removes worn jewelry.";
        'search':
            font off;
            print "  search the rubble^";
            print "  search the suspect^";
            font on;
            new_line;
            print "Searching can reveal something hidden.  
            Searching containers (purses or filing cabinets) is the same as
            LOOKing in the bag.  On the other hand searching a pile of rubble 
            makes more sense grammatically.  ";
            print "Do not say what you are searching _for_: 
            SEARCH FOR SPECTACLES will usually fail.";
        'switch':
            font off;
            print "  switch the lamp on^";
            print "  switch the tv on^";
            print "  turn the tv off (alternative form)^";
            font on;
            new_line;
            print "Turns a switchable thing on or off.";
        'take', 'get':
            font off;
            print "  get the wooden spoon^";
            print "  take the brass lantern^";
            print "  take all from the treasure chest (takes all the things)^";
            font on;
            new_line;
            print "Take or get a thing into your inventory.  If something 
            cannot be taken the story will tell you so.  Note that you can use
            the ~all~ word to indicate taking every possible thing, furthermore 
            you can also specify taking ~from~ something - a toolbox, shelf
            or candy jar.";
        'throw':
            font off;
            print "  throw the frisbee at rex^";
            print "  throw the rock at the ogre^";
            font on;
            new_line;
            print "Throwing is a very specific verb with subtle nuances -- 
            You usually throw things AT something.  If you want to throw 
            a gold coin down a magic well, you should DROP the coin in the well 
            instead (even though in English you may say the former).";
        'transfer':
            font off;
            print "  transfer candy to treat bag^";
            print "  transfer the red potion to the carry case^";
            font on;
            new_line;
            print "Transfer is a shortcut verb which REMOVEs an item from one 
            container and INSERTs it into another, saving you from typing two
            commands.  Both containers need to be open so their contents are
            visible.";
        'tie':
            font off;
            print "  tie the bed sheet to the window frame^";
            print "  tie the rope around the tree^";
            font on;
            new_line;
            print "Tying fixes one item on another.  Not everything in the 
            story can be tied.";
        'turn':
            font off;
            print "  turn the dial^";
            print "  turn the Lazy Susan^";
            font on;
            new_line;
            print "Turns or rotates a thing.";
        'wear':
            font off;
            print "  wear the top hat^";
            print "  wear the pearl necklace^";
            font on;
            new_line;
            print "Puts a garment or jewelry on.";
    }
    new_line;
    new_line;
];

!---------------------------------------------------------------------------
! Introductions
!--------------------------------------------------------------------------- 

[ LongIntro;
	BasicBrief();
	new_line;
	BasicIntro();
];

[ BasicBrief;
	print "The game you are playing is a work of Interactive Fiction, 
		you play the main character of a story and you type the actions 
        you want the character to take.^^";
    print "If this sounds daunting be assured that there is a very low 
        learning curve, and this HELP text will tell you everything 
        you need to play IF.^^";
    print "This text uses a convention where upper case words signal
        something that you can type.  It does not matter if you type in upper
        or lower case, the story will understand either way.";
];

[ BasicIntro;
    print (ESB) "INTERACTIVE FICTION^";
	print "There are various kinds of IF in the world.  Some of them put more
		emphasis on solving puzzles; some want to move you through a coherent plot
		of some kind; some want to offer you something to explore.^^";
	print "In games with a lot of challenging puzzles, you can expect to spend a fair
		amount of time wandering around trying to figure out what you should do
		next; this is part of the fun.  (If you like that sort of thing, anyway.) 
		When you start a game, you can usually get a sense fairly early on of what
		kind of game it is and what the author expects you to do.  Read the
		opening text carefully: it may tell you things about the character you are
		playing, your goals within the game, and so on.^^";
	print "If the game tells you to type ABOUT or INFO the first time you play, you
		should always do so: this information may include special commands or
		other material without which you won't be able to finish.  This is like
		the game manual in a commercial game, so don't ignore it.^^";
	print (ESB) "HOW THE WORLD IS ASSEMBLED^^";
	print "Space: Most IF games are set in a world made up of rooms without internal
		division.  Movement between rooms is possible; movement within a room does
		not always amount to anything.  >WALK OVER TO THE DESK is rarely a useful
		sort of command.  On the other hand, if something is described
		as being high or out of reach, it is sometimes relevant to stand on an
		object to increase your height.  This kind of activity tends to be
		important only if prompted by the game text.^^";
	print "Containment: One thing that IF does tend to model thoroughly is
		containment.  Is something in or on something else?  The game keeps track
		of this, and many puzzles have to do with where things are -- in the
		player's possession, lying on the floor of the room, on a table, in a box,
		etc.^^";
	print "Types of Action: Most of the actions you can perform in the world of IF
		are brief and specific.  >WALK WEST or >OPEN DOOR are likely to be
		provided.  >TAKE A JOURNEY or >BUILD A TABLE are not.  Things like >GO TO
		THE HOTEL are on the borderline: some games allow them, but most do not. 
		In general, abstract, multi-stage behavior usually has to be broken down
		in order for the game to understand it.^^";
	print "Other Characters: Other characters in IF games are sometimes rather
		limited.  On the other hand, there are also games in which character
		interaction is the main point of the game.  You should be able to get a
		feel early on for the characters -- if they seem to respond to a lot of
		questions, remember what they're told, move around on their own, etc.,
		then they may be fairly important.  If they have a lot of stock responses
		and don't seem to have been the game designer's main concern, then they
		are most likely present either as local color or to provide the solution
		to a specific puzzle or set of puzzles.  Characters in very
		puzzle-oriented games often have to be bribed, threatened, or cajoled into
		doing something that the player cannot do -- giving up a piece of
		information or an object, reaching something high, allowing the player
		into a restricted area, and so on.^^";
	rtrue;
];


!---------------------------------------------------------------------------
! Explain Prompt, Starting Instructions, Stuck Instructions
!--------------------------------------------------------------------------- 


[ ExplainPrompt;
	print (ESB) "PROMPT^";
	print "The ", (ESB) ">", " sign is where the game says, ~Okay, what do you
		want to do now?~  You may respond by typing an instruction -- usually an
		imperative verb, possibly followed by prepositions and objects.  So, for
		instance, LOOK, LOOK AT FISH, TAKE FISH.^";
];

[ StartingInstructions;
	print (ESB) "GETTING STARTED^";
	print "The first thing you want to do when starting a game is acquaint yourself
		with your surroundings and get a sense of your goal:^^";
	print (ESB) "Read the introductory text carefully.  ", "Sometimes it contains clues.  ";
	print (ESB) "LOOK at the room description.  ", "Get an idea of what sort of 
		place you're in.  Usually the description will tell you 
		where the exits are, and any items that you can interact with.  
        Type LOOK if you want to see the room description.  ";
	print (ESB) "EXAMINE the things in the room.  ", "Item descriptions can 
		contain clues to help you out.  ";
	print (ESB) "Examine self.  ", "To see your own appearance.  ";
	print (ESB) "TAKE INVENTORY (I).  ", "To list everything you are carrying.  ";
	print (ESB) "GO NORTH.  ", "Move from room to room, and check out every location
		available.^^";
];

[ StuckInstructions;
	print (ESB) "Explore.  ", "Examine every object mentioned in room descriptions, and
		everything in your inventory.  Examine yourself, too.  
		Look inside all closed containers.  Open
		all doors and go through them.  If anything is locked, that's probably a
		puzzle, and you should try to get it unlocked.^^";
	print (ESB) "Try out all your senses.  ", "If the game mentions an interesting
		texture, odor, or sound, try SMELLing, TOUCHing, LISTENing, etc.^^";
	print (ESB) "Reread.  ", "Look back at things you've already seen; sometimes this will
		trigger an idea you hadn't thought of.^^";
	print (ESB) "Take hints from the prose.  ",
		"Things that are described in great
		detail are probably more important than things that are given one-liners.
		Play with those things.  If there is a hole, or container, look inside it.^^";
	print (ESB) "Consider the genre of the game.  ",
		"Mysteries, romances, and thrillers all
		have their own types of action and motivation.  What are you trying to do,
		and how do conventional characters go about doing that?  What's the right
		sort of behavior for a detective/romance heroine/spy?^^";
	print (ESB) "Play with someone else.  ", "Two heads are usually better than one.^^";
	print (ESB) "As a last resort.  ", "If you are stuck and don't know how to
	progress the story, you can ask Dr Hint by typing HINT.^^";
	"Good luck!^^";
];


!---------------------------------------------------------------------------
! Standard Verbs list
!--------------------------------------------------------------------------- 

[ StandardVerbs;

	print "Here is a list of verbs you can use in this story. 
    To read more about a specific verb, type HELP followed by the verb.^^";
    
    print (ESB) "Seeing Things^";

#ifdef TARGET_GLULX;
	glk_set_style(style_Preformatted);
#ifnot;	
	font off;
#endif;

    print "CONSULT    ";
    print "EXAMINE    ";
    print "INVENTORY  ";
    new_line;
    print "LOOK       ";
    print "READ       ";
    print "SEARCH     ";
    new_line;

#ifdef TARGET_GLULX;
	glk_set_style(style_Normal);
#ifnot;	
	font on;
#endif;

    print (ESB) "^Moving Around^";

#ifdef TARGET_GLULX;
	glk_set_style(style_Preformatted);
#ifnot;	
	font off;
#endif;

	print "NORTH [N]  ";
	print "SOUTH [S]  ";
	print "EAST  [E]  ";
	print "WEST	 [W]  ";
	new_line;
	print "[NE]       ";
	print "[NW]       ";
	print "[SE]       ";
	print "[SW]       ";
	new_line;
	print "UP         ";
	print "DOWN       ";
	print "IN         ";
	print "OUT        ";
	new_line;
    print "CLIMB      ";
	print "ENTER      ";
	print "EXIT       ";
	new_line;

#ifdef TARGET_GLULX;
	glk_set_style(style_Normal);
#ifnot;	
	font on;
#endif;

    print (ESB) "^Manipulating Things^";

#ifdef TARGET_GLULX;
	glk_set_style(style_Preformatted);
#ifnot;	
	font off;
#endif;

    print "BLOW       ";
    print "BREAK      ";
    print "BURN       ";
    print "CLOSE      ";
    print "CUT        ";!
    new_line;
    print "DIG        ";
    print "DROP       ";
    print "EMPTY      ";!
    print "FILL       ";
    print "LIGHT      ";
    new_line;
    print "LOCK       ";
    print "OPEN       ";
    print "PULL       ";
    print "PUSH       ";
    print "PUT        ";
    new_line;
    print "REMOVE     ";
    print "SET        ";
    print "SWITCH     ";
    print "TAKE       ";
    print "THROW      ";
    new_line;
    print "TIE        ";
    print "TRANSFER   ";!
    print "TURN       ";
    print "UNLOCK     ";
    print "WEAR       ";
    new_line;
    
#ifdef TARGET_GLULX;
	glk_set_style(style_Normal);
#ifnot;	
	font on;
#endif;

    print (ESB) "^Other Physical Actions^";

#ifdef TARGET_GLULX;
	glk_set_style(style_Preformatted);
#ifnot;	
	font off;
#endif;
	
    print "ATTACK     ";
    print "BUY        ";
    print "JUMP       ";
    print "RUB        ";
	new_line;
    print "SLEEP      ";
    print "SWIM       ";
    print "SWING      ";
	print "SQUEEZE    ";
	new_line;
    print "WAIT       ";
    print "WAKE       ";
    print "WAVE       ";
    new_line;
	
#ifdef TARGET_GLULX;
	glk_set_style(style_Normal);
#ifnot;	
	font on;
#endif;

    print (ESB) "^Using Your Senses^";

#ifdef TARGET_GLULX;
	glk_set_style(style_Preformatted);
#ifnot;	
	font off;
#endif;
	
    print "EAT        ";
    print "DRINK      ";
	print "LISTEN     ";
    print "SMELL      ";
    new_line;
    print "SING       ";
	print "TASTE      ";
	print "TOUCH      ";
	print "THINK      "; 
	new_line;

#ifdef TARGET_GLULX;
	glk_set_style(style_Normal);
#ifnot;	
	font on;
#endif;

    print (ESB) "^Interacting with others^";

#ifdef TARGET_GLULX;
	glk_set_style(style_Preformatted);
#ifnot;	
	font off;
#endif;

    print "ASK ABOUT  ";
    print "ASK FOR    ";
    print "GIVE       ";
    new_line;
    print "ANSWER     ";
    print "KISS       ";
	print "SAY        ";
	print "SHOW       ";
    print "TELL       ";
	new_line;
    new_line;
	
#ifdef TARGET_GLULX;
	glk_set_style(style_Normal);
#ifnot;	
	font on;
#endif;
];

[ GameCommands flag;
    print (ESB) "Game Commands^";

    #ifdef TARGET_GLULX;
    glk_set_style(style_Preformatted);
    #ifnot;	
    font off;
    #endif; 

    print "RESTART    RESTORE     SAVE^";
    print "QUIT       UNDO        PRONOUNS^";
    print "SCRIPT ON  SCRIPT OFF  VERIFY^";

    #ifndef NO_PLACES;
    print "OBJECTS    PLACES     ^";
    #endif;
    #ifdef MAX_SCORE; 
    if (max_score > 0)
    {	print "SCORE      ";
        print "NOTIFY ON  ";
        print "NOTIFY OFF ";
        flag = 1;
    }
    #endif; 
    #ifdef TASKS_PROVIDED;
    if (max_score > 0)
    {
        print "FULL SCORE";
        flag = 1;
    }
    #endif;
    if (flag) print "^";
    new_line;
    #ifdef TARGET_GLULX;
    glk_set_style(style_Normal);
    #ifnot;	
    font on;
    #endif;
];

[ Abbreviations; 
	print (ESB) "Abbreviations:^";

#ifdef TARGET_GLULX;
	glk_set_style(style_Preformatted);
#ifnot;	
	font off;
#endif;

	!print "D -- DOWN.^";
	!print "E -- EAST.^";
	!print "G -- AGAIN.^";
	!print "I -- INVENTORY.^";
	!print "L -- LOOK.^";
	!print "N -- NORTH.^";
	!print "NE -- NORTHEAST.^";
	!print "NW -- NORTHWEST.^";
	!print "Q -- QUIT.^";
	!print "S -- SOUTH.^";
	!print "SE -- SOUTHEAST.^";
	!print "SW -- SOUTHWEST.^";
	!print "U -- UP.^";
	!print "W -- WEST.^";
	!print "X -- EXAMINE.^";
	!print "Z -- WAIT.^";
    print "AGAIN [G]      ";
	print "DOWN [D]       ";
	print "EAST [E]       ";
	print "LOOK [L]       ";
    print "^";
	print "NORTH [N]      ";
	print "QUIT [Q]       ";
	print "SOUTH [S]      ";
	print "UP [U]         ";
    print "^";
	print "WEST [W]       ";
    print "WAIT [Z]       ";
    print "EXAMINE [X]    ";
    print "INVENTORY [I]  ";
    print "^";
    print "NORTHEAST [NE] ";
    print "NORTHWEST [NW] ";
    print "SOUTHEAST [SE] ";
    print "SOUTHWEST [SW] ";
    print "^";

#ifdef TARGET_GLULX;
	glk_set_style(style_Normal);
#ifnot;	
	font on;
#endif;
    
	print "^";
    print "AGAIN repeats the last entered command, ";
    print "and ~it~ refers to the last item handled, eg:^";

#ifdef TARGET_GLULX;
	glk_set_style(style_Preformatted);
#ifnot;	
	font off;
#endif;

    print "> EXAMINE THE LANTERN^";
    print "> TAKE IT^";
    
#ifdef TARGET_GLULX;
	glk_set_style(style_Normal);
#ifnot;	
	font on;
#endif;
    
    print "^";
];

!---------------------------------------------------------------------------
! Communication etc.
!--------------------------------------------------------------------------- 

[ AllCommunication;
	Communication();
	OnMovement();
	OnObjects(); 
	OnNPCs();
	MetaCommands();
];

[ Communication; 
	print (ESB) "BASICS^";
	print "In order to communicate with the game, you will need to enter 
		instructions beginning with verbs, as if you are giving orders
        to someone.  The story recognizes a limited number of verbs, all of
        which are listed with HELP VERBS.^^";
	print "You may use articles (~the~ and ~a~), but you do not need to.  
        GO NORTH, TAKE THE BRASS LANTERN, or LOOK UNDER THE CARPET are 
        examples of how verbs and nouns are used.^^";
];
[ OnMovement; 
	print (ESB) "ROOMS AND TRAVEL^"; 
	print "At any given time, you are in a specific area or room.  When you
		enter a room the game will print a description of what you can see
		there.  This description will contain two vital kinds of information:
		things in the room you can interact with or take, and a list of 
		exits, or ways out.  If you want to see the room description again, 
		just type LOOK.^^";
	print "When you want to leave a location and go to another one 
		use a compass direction: eg, GO NORTH. 
		For brevity you are allowed to omit the word GO, and
		to abbreviate the compass direction.  So you have 
		NORTH, SOUTH, EAST, WEST, NORTHEAST, SOUTHEAST, NORTHWEST,
		SOUTHWEST, UP, and DOWN, or in short form N, S, E, W, NE, SE, NW, SW,
		U, and D.^^";
    print "UP and DOWN are reserved for climbing in that direction - ropes, 
        ladders, stairs, sheets tied outside a window are all examples 
        of climbable things.^^";
	print "In some locations, IN and OUT will also be useful, the story will
        indicate to you when you can go in or out of a specific place.^^";
];
[ OnObjects;
	print (ESB) "THINGS^";
	print "The story contains an assortment of things that you can
		interact with.  Most importantly, you may TAKE or GET items, and (when
		you are tired of them) DROP them again.  INVENTORY (abbreviated I)
		will list the items you are currently carrying.^^";
	print "There are usually assorted things you may do with these objects.
		OPEN, CLOSE, WEAR, EAT, LOCK, and UNLOCK are especially common.^^";
	print "Occasionally, you will find that the game does not recognize the
		name of an object even though it has been described as being in the room
		with you.  If this is the case, the object is just there for scenery,
		and you may assume that you do not need to interact with it.^^";
]; 
[ OnNPCs;
	print (ESB) "OTHER CHARACTERS^"; 
#ifdef NPC_MENU;
	MenuNPC();
	rtrue;
#endif;
#ifdef NPC_TALKTO;
	TalkToNPC();
	rtrue;
#endif;
#ifdef NPC_TOPIC;
	TopicMenuNPC();
	rtrue;
#endif; 
	AskTellNPC(); 
	rtrue;
];

[ AskTellNPC;
	print "From time to time you will meet other people and creatures. You will be unable to
		converse with the people in plain English; instead, a more constrained system of
		communication is used. Here are some common ways to talk to characters:^^";
    print "Say something to them. If there is only one character near you, then
    you do not have to type in whom you are referring to.^";
    print (ESB) ">SAY HI^";
    print (ESB) ">SAY HI TO THE CHESSIRE CAT^^";
	print "Ask them about a thing.^";
	print (ESB) ">ASK PAUL ABOUT HIS BROTHER^";
	print (ESB) ">ASK GLENDA ABOUT RUBY SLIPPERS^^";
	print "Show them a thing.^";
	print (ESB) ">SHOW WARRANT TO DRUG LORD^";
	print (ESB) ">SHOW BUCKET OF WATER TO EVIL WITCH^^";
	print "Tell them about a thing.^";
	print (ESB) ">TELL ICE CREAM VENDOR ABOUT HIS TRUCK^";
	print (ESB) ">TELL DOROTHY ABOUT FLYING MONKEYS^^";
	print "Command them to do something.^";
	print (ESB) ">TINY TIM, PUT THE UKELELE ON THE TABLE^";
	print (ESB) ">TIN MAN, GET UP. CARRY US^^";
];

[ MenuNPC;
	print "From time to time you will meet other people and creatures. You may use the command
		>TALK TO CHARACTER, and the game will give you a menu of options, which you may
		use to converse with the character in plain English.^^";
	print "You may also find it useful to show them things:^^"; 
	print (ESB) ">SHOW WARRANT TO DRUG LORD^";
	print (ESB) ">SHOW BUCKET OF WATER TO EVIL WITCH^^";
	print "or give them instructions:^";
	print (ESB) ">FREDDY, HELLO^";
	print (ESB) ">TINY TIM, PUT THE UKELELE ON THE TABLE^^";
	print "but if you're just not getting through, rely on the menus.^";
];
[ TalkToNPC;
	print "From time to time you will meet other people and creatures. You will be unable to
		converse with the people in plain English; instead, you may use the command
		>TALK TO CHARACTER, and the game will decide what you should say at this
		juncture.^"; 
];

[ TopicMenuNPC;
	print "From time to time you will meet other people and creatures. You will be unable to
		converse with the people in plain English; instead, a more constrained system of
		communication is used. There are three common ways to talk to characters:^^"; 
	print "Bring up a topic for conversation.^";
	print (ESB) ">TELL BOB ABOUT THE FLAG^";
	print (ESB) ">ASK BETTY ABOUT CHOCOLATE CAKE^^";
	print "These can also be abbreviated to A and T, and the game will also
		keep track of which person you're talking to, if you've already started a 
		conversation.  This allows briefer commands, like so:^^";
	print (ESB) ">A CAKE^";
	print (ESB) ">T FLAG^^";
	print "If there is more than one thing you are allowed to ask Betty about the chocolate 
		cake, the game will give you a menu of options in the window at the bottom of the 
		screen.  Otherwise, it will carry out your instruction immediately.^^";
	print "Show them an object.^";
	print (ESB) ">SHOW WARRANT TO DRUG LORD^";
	print (ESB) ">SHOW BUCKET OF WATER TO EVIL WITCH^^"; 
	print "Command them.^"; 
	print (ESB) ">TINY TIM, PUT THE UKELELE ON THE TABLE^";
	print (ESB) ">TIN MAN, GET UP. CARRY US^^";
	print "Most characters will be less than responsive to commands.^";
];

[ MetaCommands;
	print (ESB) "SYSTEM COMMANDS^";
	print "There are a few simple commands for managing your story progress:^^";
	print (ESB) "SAVE", " -- Saves a story progress, to RESTORE later.^";
	print (ESB) "RESTORE", " -- Restore a previously saved story.^";
	print (ESB) "RESTART", " -- Restart the story from the beginning.^";
	print (ESB) "SCORE", " -- Prints your score.^";
	print (ESB) "FULL", " -- Lists each completed task that scored points.^";
	print (ESB) "QUIT", " -- Ends the story.^^";
];


!---------------------------------------------------------------------------
! About the IF community online
!--------------------------------------------------------------------------- 

[ OnlineHelp;
	print (ESB) "IF HELP ONLINE^^";
		print "Some online sources of introductory help for IF games include:^^";
		print "Frederik Ramsberg's Beginner's Guide, http://www.octagate.com/Fredrik/IFGuide/^";
		print "Interactive Fiction -- Getting Started, http://adamcadre.ac/content/if.txt^";
		print "A Brief Introduction to Interactive Fiction, http://www.tads.org/if.htm^^";
		print "For more information about IF, the IF community, and other games to play,
			you should also try:^^";
		print "Brasslantern, http://www.brasslantern.org/^";
		print "Baf's Guide to Interactive Fiction, http://www.wurb.com/if/index^^";
		print "You may also ask for specific information and game hints on the newsgroup
			rec.games.int-fiction.^^";
		print "If you are not familiar with newsgroups and don't have
			a newsreader already set up, you may access it by going to http://groups.google.com/
			and selecting ~rec~, then ~rec.games~, then ~rec.games.int-fiction.~  You will
			be presented with a long list of things that people are already talking about.  
			If you've never read this newsgroup before, you should look for a thread with the
			word ~FAQ~ in the title, and read it: this will give you instructions about how
			to post without breaking any of the community's rules of etiquette.  (They're
			not especially fussy, but following them will get you prompter and more polite 
			assistance.)^^";
		print "Once you've done that, you may post
			a new message with a clearly labelled subject (like ~[HINT REQUEST] Jigsaw~ or
			~Looking for Mystery Games~).  Afterwards, wait a few hours and check the newsgroup again
			to see whether anyone has an answer for you.^^";
];


[ MoreGames;
	print (ESB) "MORE SOURCES OF IF^^";
	print "There are more games like this at the IF Archive, www.ifarchive.org.^^";
	print "Instructions on setting them up are available from Frederik Ramsberg's 
		Beginner's Guide, http://www.octagate.com/Fredrik/IFGuide/^";
	print "Guides to good IF (for beginners or in general) are to be found at the Beginner's
		Guide just mentioned, or at Baf's Guide to Interactive Fiction, 
		http://www.wurb.com/if/index.";
];

Verb meta 'about' * -> About;
Verb meta 'credits' * -> Credits;