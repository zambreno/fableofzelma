/*****************************************************************************
 * Joseph Zambreno
 * Department of Electrical and Computer Engineering
 * Iowa State University
 *****************************************************************************/


/*****************************************************************************
 * fableofzelma.cpp - The Fable of Zelma application. Takes as input move files
 * and an optional map file and runs a Legend of Zelda-style simulation
 * for up to four teams.
 *
 *
 * NOTES:
 * 1/24/14 by JAZ::Design created.
 *****************************************************************************/

#include "fableofzelma.hpp"

foz::Game *myGame;

int main(int argc, char *argv[]) {

    myGame = new(std::nothrow)foz::Game(argc,argv);
    myGame->init();
    myGame->printConfig();

    myGame->initSFML();
    myGame->loadResources();
    //return 0;
    myGame->mainLoop();

    delete myGame;
    return 0;
}

namespace foz {

    /*****************************************************************************
    * Function: Game::init()
    * Description: Initializes the game environment after compiling the team and
    * map files.
    *****************************************************************************/
    void Game::init() {
        // Set the random seed here
        srand(0);
        myWorld.compile(&myConfig, &myStatus);
        compileTeams();

        // Initialize game status
        myStatus.mode = GAME_START;
        framecount = 0;
        for (uint8_t i = 0; i < 4; i++) {
            myStatus.scores[i] = 0;
            myTeams[i].id = i;
            myTeams[i].cur_cmd = 0;
            myTeams[i].cur_link = 0;
            myTeams[i].cmds_done = false;
            myTeams[i].cur_cmdframe = 0;
            myTeams[i].cur_cmdopt = 0;
        }

    }


    /*****************************************************************************
    * Function: Game::reset()
    * Description: Resets the game environment
    *****************************************************************************/
    void Game::reset() {

        for (uint8_t i = 0; i < 4; i++) {
            myLinks[i].clear();
        }

        init();
        myStatus.mode = GAME_START;

    }

    /*****************************************************************************
    * Function: Game::mainLoop()
    * Description: Runs the main update, drawing, and event processing loop.
    *****************************************************************************/
    void Game::mainLoop() {


        while (myWindow.isOpen()) {
            processEvents();
            switch (myStatus.mode) {
                case GAME_START:
                case GAME_MID:
                    myCamera.update(false);
                    myWorld.draw();
                    drawScoreboard();

                    updateGame();
                   break;
                case GAME_END:
                    endGame();
                    break;
                default:
                    break;

            }
            myWindow.display();
        }

        return;

    }


    /*****************************************************************************
    * Function: Game::updateGame()
    * Description: Updates all the main elements of the game.
    *****************************************************************************/
    void Game::updateGame() {

        int CMDFRAMEMAX;

        // Command loop: grab the next cmd for each team.
        for (uint16_t i = 0; i < 4; i++) {

            // If we are done with the commands, move on to the next team
            if (myTeams[i].cmds_done == true) {
                continue;
            }

            // If we are done with the active links, move on to the next team
            if (myTeams[i].cur_link > myLinks[i].size()) {
                myTeams[i].cmds_done = true;
                continue;
            }

            // Grab the current command and link
            foz::cmd_type *mycmd = &myTeams[i].cmds[myTeams[i].cur_cmd];
            foz::Link *myLink = &myLinks[i][myTeams[i].cur_link];

            //the vertices of link and each object for easier access
            bool pred_true = true;
            switch (mycmd->cmd) {

                case MOVE_CMD:
                    CMDFRAMEMAX = 20;

                    //check to see is an object will keep Link from moving
                    myLink->can_move = true; //Link can move unless we find something in his way

                    if (i==0) {
                        //printf("RoomX %d RoomY %d Size %d\n",myLink->room_x,myLink->room_y,myLink->id);
                    }
                    for (uint16_t obj = 0; obj < myWorld.myRooms[myLink->room_y][myLink->room_x].myObjects.size(); obj++) {
                        foz::Object *myObject = &myWorld.myRooms[myLink->room_y][myLink->room_x].myObjects[obj];
                        if (i==0) {
                            //printf("%d:type %d\n",obj,myObject->type);
                        }
                        if (linkColObj(myLink,myObject)) {
                            if (myObject->status == SOLID) {
                                myLink->can_move = false;
                            }else {
                                if (myObject->texfile==TEX_RUPEE) {
                                    myTeams[myLink->team].score++;
                                    myObject->active = false;
                                    //printf("Roomx: %d, Roomy: %d LINK: %d\n",myLink->room_x,myLink->room_y,i);
                                }
                            }
                        }
                        if (!myObject->active) {
                            myWorld.myRooms[myLink->room_x][myLink->room_y].myObjects.erase(myWorld.myRooms[myLink->room_x][myLink->room_y].myObjects.begin()+obj);
                            obj--;
                        }
                    }

                    if (myLink->y < -330) {
                        if (myLink->direction == DIRECTION_SOUTH) {
                            if (myWorld.myRooms[myLink->room_x][myLink->room_y].myTiles[6][12] == 50 && (myLink->x > -50)&&(myLink->x < 0)) {
                                myLink->room_y++;
                                myLink->y = 329;
                            }else {
                                myLink->y = -330;
                            }
                        }
                    }else if (myLink->y > 290) {
                        if (myLink->direction == DIRECTION_NORTH) {
                            if (myWorld.myRooms[myLink->room_x][myLink->room_y].myTiles[6][0] == 50 && (myLink->x > -50)&&(myLink->x < 0)) {
                                myLink->room_y--;
                                myLink->y = -329;
                            }else {
                                myLink->y = 290;
                            }
                        }
                    }else if (myLink->x > 290) {
                        if (myLink->direction == DIRECTION_EAST) {
                            if (myWorld.myRooms[myLink->room_x][myLink->room_y].myTiles[12][6] == 50 && (myLink->y > -50) && (myLink->y < 0)) {
                                myLink->room_x++;
                                myLink->x = -329;
                            }else {
                                myLink->x = 290;
                            }
                        }
                    }else if (myLink->x < -330) {
                        if (myLink->direction == DIRECTION_WEST) {
                            if (myWorld.myRooms[myLink->room_x][myLink->room_y].myTiles[0][6] == 50 && (myLink->y > -50) && (myLink->y < 0)) {
                                myLink->room_x--;
                                myLink->x = 289;
                            }else {
                                myLink->x = -329;
                            }
                        }
                    }

                    if (myLink->can_move) {
                        myLink->update(mycmd->cmd);
                    }

                    myTeams[i].cur_cmdframe++;

                    // Have we reached the end of a CMDFRAME?
                    // If so, see how many squares we have left to go.
                    if (myTeams[i].cur_cmdframe >= CMDFRAMEMAX) {
                        myTeams[i].cur_cmdframe = 0;
                        myTeams[i].cur_cmdopt++;
                        if (myTeams[i].cur_cmdopt >= mycmd->opt[0]) {
                            myTeams[i].cur_cmd++;
                            myTeams[i].cur_cmdopt = 0;
                        }
                    }
                    break;

                case ATTACK_CMD:
                    CMDFRAMEMAX = 20;

                    myTeams[i].cur_cmdframe++;
                    myLink->update(mycmd->cmd);

                    if (myTeams[i].cur_cmdframe >= CMDFRAMEMAX) {
                        myTeams[i].cur_cmdframe = 0;
                        myTeams[i].cur_cmd++;
                    }
                    break;

                case LEFT_CMD:
                case RIGHT_CMD:
                    myLink->update(mycmd->cmd);
                    myTeams[i].cur_cmd++;
                    break;

                default:
                    bool pred_true = true;

                    //Handles the goto command
                    if (myTeams[i].cmds[myTeams[i].cur_cmd].cmd == GOTO_CMD){
                        for (uint16_t j = 0; j < myTeams[i].cmds.size(); j++) {
                            if (strcmp(myTeams[i].cmds[j].label_str,myTeams[i].cmds[myTeams[i].cur_cmd].target_str)==0){
                                myTeams[i].cur_cmd = j;
                                mycmd = &myTeams[i].cmds[myTeams[i].cur_cmd];
                                break;
                            }
                        }
                    }else if((mycmd->cmd != GOTO_CMD) || (pred_true == false)) {
                        printf("Unrecognized Team: %d cmd: %s %d\n",i,cmdNames[myTeams[i].cmds[myTeams[i].cur_cmd].cmd][0].c_str(),myTeams[i].cur_cmd);
                        myTeams[i].cur_cmd++;
                        if (myTeams[i].cur_cmd >= myTeams[i].cmds.size()) {
                            myTeams[i].cmds_done = true;
                        }
                    }

                    break;
            }

            if (myTeams[i].cur_cmd >= myTeams[i].cmds.size()) {
                myTeams[i].cmds_done = true;
            }

        }


        //update time
        myStatus.time_ms -= 1000.0/FRAME_RATE;
        if (myStatus.time_ms <= 0.0) {  // Check for the gameDone condition
            myStatus.time_ms = 0.0;
            myStatus.mode = GAME_END;
        }

        framecount++;
    }



    /*****************************************************************************
    * Function: Game::endGame()
    * Description: Runs the end game sequence.
    *****************************************************************************/
    void Game::endGame() {
        myCamera.update(false);
        myWorld.draw();
    }



    /*****************************************************************************
    * Function: Game::Game()
    * Description: Constructor for foz::Game() class. Reads in and parses the
    * input command line in order to set configuration data
    *****************************************************************************/
    Game::Game(int argc, char **argv) {
        int8_t i, nfiles=1;

        /* We require at least two arguments on the command line */
        if (argc < 2) {
            raise_error(ERR_USAGE, NULL);
        }

        /* If the last command-line argument is -h or --help that is ok */
        if (!strncmp(argv[argc-1], "-h", 2) || !strncmp(argv[argc-1], "--help", 6)) {
            print_help();
        }

        /* Otherwise, either the last or the last four arguments should be files */
        if (argv[argc-1][0] == '-') {
            raise_error(ERR_USAGE, NULL);
        }
        else {
            if (argc > 2) {
                if ((argv[argc-2][0] == '-') || (argv[argc-3][0] == '-')) {
                    nfiles = 1;
                }
                else {
                    if (argc < 5) {
                        raise_error(ERR_USAGE, NULL);
                    }
                    else if ((argv[argc-2][0] == '-') || (argv[argc-3][0] == '-') ||
                             (argv[argc-4][0] == '-')) {
                        raise_error(ERR_USAGE, NULL);
                    }
                    else {
                        nfiles = 4;
                    }
                }
            }
            else {
                nfiles = 1;
            }
        }

        /* Set the default values */
        myConfig.debug_level = DEBUG_DEFAULT;
        myConfig.screen_height = SCREEN_HEIGHT_DEFAULT;
        myConfig.screen_width = SCREEN_WIDTH_DEFAULT;
        myConfig.screen_depth = SCREEN_DEPTH_DEFAULT;
        myConfig.map_fname = (char *)malloc(strlen(MAP_FNAME_DEFAULT)+1);

        if (!myConfig.map_fname) {
            raise_error(ERR_NOMEM, NULL);
        }
        strcpy(myConfig.map_fname, MAP_FNAME_DEFAULT);
        for (i = 0; i < 4; i++) {
            myConfig.team_fname[i] = (char *)malloc(strlen(TEAM_FNAME_DEFAULT)+1);
            if (!myConfig.team_fname[i]) {
                raise_error(ERR_NOMEM, NULL);
            }
            strcpy(myConfig.team_fname[i], TEAM_FNAME_DEFAULT);
        }

        for (i = 1; i < argc-nfiles; i++) {
            /* Arguments must begin with '-' or '--' */
            if (argv[i][0] != '-' || strlen(argv[i]) < 2) {
                raise_error(ERR_USAGE, NULL);
            }

            /* Decode the single dash arguments */
            if (argv[i][1] != '-') {
                /* Single dash arguments should have just one character after the dash */
                if (strlen(argv[i]) > 2) {
                    raise_error(ERR_USAGE, NULL);
                }
                switch (argv[i][1]) {
                    case 'H':
                        i++;
                        sscanf(argv[i], "%hu", &myConfig.screen_height);
                        break;
                    case 'W':
                        i++;
                        sscanf(argv[i], "%hu", &myConfig.screen_width);
                        break;
                    case 'D':
                        i++;
                        sscanf(argv[i], "%d", &myConfig.debug_level);
                        break;
                    case 'M':
                        i++;
                        myConfig.map_fname = (char *)realloc(myConfig.map_fname, strlen(argv[i])+1);
                        if (!myConfig.map_fname) {
                            raise_error(ERR_NOMEM, NULL);
                        }
                        strcpy(myConfig.map_fname, argv[i]);
                        break;
                    case 'h':
                        print_help();
                        break;
                    default:
                        raise_error(ERR_USAGE, NULL);
                        break;
                }
            }

            /* Decode the double dash arguments */
            else {
                if (!strncmp(argv[i], "--height", 8)) {
                    i++;
                    sscanf(argv[i], "%hu", &myConfig.screen_height);
                }
                else if (!strncmp(argv[i], "--width", 7)) {
                    i++;
                    sscanf(argv[i], "%hu", &myConfig.screen_width);
                }
                else if (!strncmp(argv[i], "--debug", 7)) {
                    i++;
                    sscanf(argv[i], "%d", &myConfig.debug_level);
                }
                else if (!strncmp(argv[i], "--map", 5)) {
                    i++;
                    myConfig.map_fname = (char *)realloc(myConfig.map_fname, strlen(argv[i])+1);
                    if (!myConfig.map_fname) {
                        raise_error(ERR_NOMEM, NULL);
                    }
                    strcpy(myConfig.map_fname, argv[i]);
                }
                else if (!strncmp(argv[i], "--help", 6)) {
                    print_help();
                }
                else {
                    raise_error(ERR_USAGE, NULL);
                }
            }
        }

        /* The last nfiles command arguments are the input file names */
        for (i = argc-nfiles; i < argc; i++) {
            myConfig.team_fname[i-(argc-nfiles)] =
                (char *)realloc(myConfig.team_fname[i-(argc-nfiles)], strlen(argv[i])+1);
            if (!myConfig.team_fname[i-(argc-nfiles)]) {
                raise_error(ERR_NOMEM, NULL);
            }
            strcpy(myConfig.team_fname[i-(argc-nfiles)], argv[i]);
        }

        return;
    }



    /*****************************************************************************
    * Function: Game::compileTeams()
    * Description: Compiles the 4 team .fpl files to initialize commands and
    * other per-team information
    *****************************************************************************/
    void Game::compileTeams() {
        foz::Team *team;
        FILE *team_file;

        for (uint8_t i_team = 0; i_team < 4; i_team++) {
            bool first_link = true;

            /* Open and compile the team file */
            if (myConfig.debug_level > 1) {
                printf("\n\nCompiling team file %s\n", myConfig.team_fname[i_team]);
            }

            team_file = fopen(myConfig.team_fname[i_team], "r");
            if (!team_file) {
                raise_error(ERR_NOFILE2, myConfig.team_fname[i_team]);
            }

            myStatus.scores[i_team] = 0;
            team = &myTeams[i_team];

            // Copy the file name, removing the .zuf extension
            team->name = (char *)calloc(strlen(myConfig.team_fname[i_team])-3, sizeof(char));
            if (!team->name) {
                raise_error(ERR_NOMEM, (char *)"team->name");
            }
            strncpy(team->name, myConfig.team_fname[i_team], strlen(myConfig.team_fname[i_team])-4);
            strlower(team->name);


            bool select_done = false;
            bool start_done = false;
            for (uint32_t line_count=1; !feof(team_file); line_count++) {
                char *fgets_ret;
                char linebuf[256], select_str1[16], select_str2[16], start_str[256];
                char place_str[16], label_str[256], target_str[256];
                char cmd_str[256], cmd_str2[256], pred_str[256];
                uint8_t select_ntok, start_ntok, label_ntok, pred_ntok, cmd_ntok;
                uint16_t select_tok;
                fgets_ret = fgets(linebuf, 256, team_file);
                select_str1[0] = 0;select_str2[0] = 0;

                strlower(linebuf);

                // If we have a '#', the line is a comment and we can skip it
                // We can also skip blank lines
                if ((fgets_ret == NULL) || (linebuf == 0) || (linebuf[0] == '#') ||
                    (linebuf[0] == 10) || (linebuf[0] == 13)) {
                    continue;
                }


                bool select_match = false;
                bool link_match = false;

                foz::Link *local_link;

                // Select instructions are first.
                select_ntok = sscanf(linebuf, " %s l%hu %s", select_str1, &select_tok, select_str2);
                if (select_ntok == 3) {
                    for (uint8_t i = 0; i < NUM_CMD_SPELLINGS; i++) {
                        if (!strcmp(select_str1, cmdNames[SELECT_CMD][i].c_str())) {
                            select_match = true;
                            break;
                        }
                    }

                    // Selection commands have to come before everything else
                    if ((select_match == true) && (select_done == true)) {
                        printf("Error compiling %s, line %d\n", myConfig.team_fname[i_team], line_count);
                        printf("  cannot select links at run-time\n");
                        raise_error(ERR_BADFILE2, myConfig.team_fname[i_team]);
                    }


                    // We should have matched a valid select command at this point
                    if (select_match == false) {
                        goto L1;
                    }

                    // It's a valid command, let's see what we selected
                    for (uint8_t l = 0; l < NUM_LINK_TYPE; l++) {
                        for (uint8_t i = 0; i < NUM_LINK_SPELLINGS; i++) {
                            if (!strcmp(select_str2, linkNames[l][i].c_str())) {
                                link_match = true;
                                break;
                            }
                        }
                        if (link_match == true) {

                            // Did we duplicate a link ID?
                            for (uint16_t l2 = 0; l2 < myLinks[i_team].size(); l2++) {
                                if (myLinks[i_team][l2].id == select_tok) {
                                    printf("Error compiling %s, line %d\n", myConfig.team_fname[i_team], line_count);
                                    printf("  duplicate link ID - link%hu was already selected\n", select_tok);
                                    raise_error(ERR_BADFILE2, myConfig.team_fname[i_team]);
                                }
                            }

                            myTeams[i_team].budget += linkCosts[l];
                            if (myTeams[i_team].budget > myStatus.budget) {
                                printf("Error compiling %s, line %d\n", myConfig.team_fname[i_team], line_count);
                                printf("  team is over budget\n");
                                printf("  budget limit is %hu\n", myStatus.budget);
                                raise_error(ERR_BADFILE2, myConfig.team_fname[i_team]);
                            }
                            local_link = new Link(l, select_tok, i_team, myWorld.width, myWorld.height);
                            local_link->active = first_link;
                            first_link = false;
                            myLinks[i_team].push_back(*local_link);
                            delete local_link;
                            break;
                        }
                    }

                    if (link_match == false) {
                        printf("Error compiling %s, line %d\n", myConfig.team_fname[i_team], line_count);
                        printf("  invalid link type\n");
                        raise_error(ERR_BADFILE2, myConfig.team_fname[i_team]);
                    }
                }


                // If we didn't match a select, we must be done with that command-type
                if (select_match == true) {
                    continue;
                }

                L1: select_done = true;

                // Until we reach the start line, we do not support predicates
                foz::cmd_type *local_cmd;
                start_str[0] = 0;
                start_ntok = 0;
                if (start_done == false) {
                    start_ntok = sscanf(linebuf, " start: %[^\t\n]", start_str);
                    if (start_ntok == 1) {
                        start_done = true;
                    }
                }

                // Everything from here on out is a proper command, with potentially labels and predicates
                cmd_str[0] = 0;label_str[0] = 0;
                bool has_label = false;
                label_ntok = sscanf(linebuf, "%[^:]: %[^\t\n]", label_str, cmd_str);
                if (label_ntok == 2) {
                    has_label = true;
                }
                else {
                    if (start_str[0] > 0) {
                        strcpy(label_str ,"start");
                        strcpy(cmd_str , start_str);
                        start_str[0] = 0;
                    } else{
                        sscanf(linebuf, " %[^\t\n]", cmd_str);
                    }
                }

                // Check for an if statement
                cmd_str2[0] = 0;
                pred_str[0] = 0;
                bool has_pred = false;
                bool inv_pred = false;
                bool has_link_pred = false;
                uint16_t pred_tok;
                uint16_t link_pred = 0;
                pred_ntok = sscanf(cmd_str, " if not l%hu.%[^,], %[^\t\n]", &pred_tok, pred_str, cmd_str2);
                if (pred_ntok == 3) {
                    has_pred = true;
                    has_link_pred = true;
                    link_pred = pred_tok;
                    inv_pred = true;
                }
                else {
                    pred_ntok = sscanf(cmd_str, " if l%hu.%[^,], %[^\t\n]", &pred_tok, pred_str, cmd_str2);
                    if (pred_ntok == 3) {
                        has_pred = true;
                        has_link_pred = true;
                        link_pred = pred_tok;
                        inv_pred = false;
                    }
                    else {
                        pred_ntok = sscanf(cmd_str, " if not %[^,], %[^\t\n]", pred_str, cmd_str2);
                        if (pred_ntok == 2) {
                            has_pred = true;
                            inv_pred = true;
                        }
                        else {
                            pred_ntok = sscanf(cmd_str, " if %[^,], %[^\t\n]", pred_str, cmd_str2);
                            if (pred_ntok == 2) {
                                has_pred = true;
                                inv_pred = false;
                            }
                            else {
                                sscanf(cmd_str, " %[^\t\n]", cmd_str2);
                            }
                        }
                    }
                }
                // If there is a predicate, check if the condition is valid
                bool pred_match = false;

                uint8_t pred = ALWAYS_PRED;
                if (has_pred == true) {
                    for (pred = 0; pred < NUM_PRED_TYPES; pred++) {
                        for (uint8_t i = 0; i < NUM_PRED_SPELLINGS; i++) {
                            if (!strcmp(pred_str, predNames[pred][i].c_str())) {
                                pred_match = true;
                                break;
                            }
                        }
                        if (pred_match == true) {
                            break;
                        }
                    }
                    if (pred_match == false) {
                        printf("Error compiling %s, line %d\n", myConfig.team_fname[i_team], line_count);
                        printf("  invalid condition of %s\n", pred_str);
                        raise_error(ERR_BADFILE2, myConfig.team_fname[i_team]);
                    }
                }

                // Now we can attempt to match the actual string
                uint8_t cmd;
                bool cmd_match = false;
                for (cmd = 0; cmd < NUM_CMD_TYPES; cmd++) {
                    for (uint8_t i = 0; i < NUM_CMD_SPELLINGS; i++) {
                        if (!strncmp(cmd_str2, cmdNames[cmd][i].c_str(), cmdNames[cmd][i].size())) {
                            cmd_match = true;
                            break;
                        }
                    }
                    if (cmd_match == true) {
                        break;
                    }
                }
                if (cmd_match == false) {
                    printf("Error compiling %s, line %d\n", myConfig.team_fname[i_team], line_count);
                    printf("  invalid command of %s\n", cmd_str2);
                    raise_error(ERR_BADFILE2, myConfig.team_fname[i_team]);
                }

                // Based on the command we matched, we can grab the target of the command.
                // We know we spelled the command correctly at this point so just grab everything else
                bool valid_cmd = false;
                uint16_t opt[2] = {0, 0};
                uint16_t link = 0;
                switch (cmd) {
                  case SELECT_CMD:
                  default:
                    valid_cmd = false;
                    break;
                  case MOVE_CMD:
                    place_str[0] = 0;
                    cmd_ntok = sscanf(cmd_str2, "%s l%hu %hu", place_str, &link,  &opt[0]);
                    if (cmd_ntok == 3) {
                        valid_cmd = true;
                    }
                    break;
                  case LEFT_CMD:
                    place_str[0] = 0;
                    cmd_ntok = sscanf(cmd_str2, "%s l%hu", place_str, &link);
                    if (cmd_ntok == 2) {
                        valid_cmd = true;
                    }
                    break;
                  case RIGHT_CMD:
                    cmd_ntok = sscanf(cmd_str2, "%s l%hu", place_str, &link);
                    if (cmd_ntok == 2) {
                        valid_cmd = true;
                    }
                    break;
                  case ATTACK_CMD:
                    cmd_ntok = sscanf(cmd_str2, "%s l%hu", place_str, &link);
                    if (cmd_ntok == 2) {
                        valid_cmd = true;
                    }
                    break;

                  case GOTO_CMD:
                    place_str[0] = 0;
                    target_str[0] = 0;
                    cmd_ntok = sscanf(cmd_str2, "%s %s", place_str, target_str);
                    if (cmd_ntok == 2) {
                        // Note that goto is not necessarily valid, depending on the target string which we can only check later
                        valid_cmd = true;
                    }
                    break;
                }

                if (valid_cmd == false) {
                    printf("Error compiling %s, line %d\n", myConfig.team_fname[i_team], line_count);
                    printf("  invalid command options of %s\n", cmd_str2);
                    raise_error(ERR_BADFILE2, myConfig.team_fname[i_team]);
                }

                // FINALLY, we can allocate and add a new command to the cmds structure
                local_cmd = new cmd_type;
                local_cmd->has_label = has_label;
                if (has_label == true)
                    strncpy(local_cmd->label_str, label_str, 16);
                if (cmd == GOTO_CMD) {
                    strncpy(local_cmd->target_str, target_str, 16);
                }
                local_cmd->inv_pred = inv_pred;
                local_cmd->has_pred = has_pred;
                local_cmd->has_link_pred = has_link_pred;
                local_cmd->link_pred = link_pred;
                local_cmd->cmd = cmd;
                local_cmd->pred = pred;
                local_cmd->link = link;
                local_cmd->line = line_count;
                local_cmd->opt[0] = opt[0];
                local_cmd->opt[1] = opt[1];

                myTeams[i_team].cmds.insert(myTeams[i_team].cmds.end(), 1, *local_cmd);
                delete local_cmd;

            }


            // Only after the file is compiled can we do a second pass and verify the target strings and plant targets
            for (uint16_t i = 0; i < myTeams[i_team].cmds.size(); i++) {

                if (myTeams[i_team].cmds[i].has_link_pred == true) {
                    bool link_pred_match = false;
                    for (uint16_t p = 0; p < myLinks[i_team].size(); p++) {
                        if (myLinks[i_team][p].id == myTeams[i_team].cmds[i].link_pred) {
                            link_pred_match = true;
                            break;
                        }
                    }
                    if (link_pred_match == false) {
                        printf("Error compiling %s, line %d\n", myConfig.team_fname[i_team], myTeams[i_team].cmds[i].line);
                        printf("  command predicate plant target of link%hu not found\n", myTeams[i_team].cmds[i].link_pred);
                        raise_error(ERR_BADFILE2, myConfig.team_fname[i_team]);
                    }
                }

                if (myTeams[i_team].cmds[i].cmd == GOTO_CMD) {
                    bool goto_valid = false;
                    for (uint16_t j = 0; j < myTeams[i_team].cmds.size(); j++) {
                        if (myTeams[i_team].cmds[j].has_label == true) {
                            if (!strcmp(myTeams[i_team].cmds[j].label_str, myTeams[i_team].cmds[i].target_str)) {
                                myTeams[i_team].cmds[i].opt[0] = j;
                                goto_valid = true;
                                break;
                            }
                        }
                    }
                    if (goto_valid == false) {
                        printf("Error compiling %s, line %d\n", myConfig.team_fname[i_team], myTeams[i_team].cmds[i].line);
                        printf("  goto target of %s not found\n", myTeams[i_team].cmds[i].target_str);
                        raise_error(ERR_BADFILE2, myConfig.team_fname[i_team]);
                    }
                }
                else {
                    bool link_match = false;
                    for (uint16_t p = 0; p < myLinks[i_team].size(); p++) {
                        if (myLinks[i_team][p].id == myTeams[i_team].cmds[i].link) {
                            link_match = true;
                            break;
                        }
                    }
                    if (link_match == false) {
                        printf("Error compiling %s, line %d\n", myConfig.team_fname[i_team], myTeams[i_team].cmds[i].line);
                        printf("  link target of p%hu not found\n", myTeams[i_team].cmds[i].link);
                        raise_error(ERR_BADFILE2, myConfig.team_fname[i_team]);
                    }

                }
            }



            // Third pass, have we duplicated any labels?
            for (uint16_t i = 0; i < myTeams[i_team].cmds.size(); i++) {
                if (myTeams[i_team].cmds[i].has_label == true) {
                    for (uint16_t j = 0; j < myTeams[i_team].cmds.size(); j++) {
                        if (i == j) continue;
                        if (myTeams[i_team].cmds[j].has_label == true) {
                            if (!strcmp(myTeams[i_team].cmds[i].label_str, myTeams[i_team].cmds[j].label_str)) {
                                printf("Error compiling %s, line %d\n", myConfig.team_fname[i_team], myTeams[i_team].cmds[j].line);
                                printf("  duplicate command label of %s\n", myTeams[i_team].cmds[i].label_str);
                                raise_error(ERR_BADFILE2, myConfig.team_fname[i_team]);
                            }
                        }
                    }
                }
            }


            if (myConfig.debug_level > 50) {
                printf("\nCommands are as follows: \n");
                printf("   ID    | LINE |   LABEL   | IF? | NOT? |   PRED   |   CMD   | LINK | OPTS  \n");
                for (uint16_t i = 0; i < myTeams[i_team].cmds.size(); i++) {
                    printf("cmd-%03u: | ", i);
                    printf(" %3u | ", myTeams[i_team].cmds[i].line);
                    if (myTeams[i_team].cmds[i].has_label == true)
                        printf("%9s | ", myTeams[i_team].cmds[i].label_str);
                    else
                        printf("%9s | ", "none");
                    if (myTeams[i_team].cmds[i].has_pred == true) {
                        if (myTeams[i_team].cmds[i].has_link_pred == true)
                            printf("%3hu | ", myTeams[i_team].cmds[i].link_pred);
                        else
                            printf("%3s | ", "yes");
                    }
                    else {
                        printf("%3s | ", "no");
                    }
                    if (myTeams[i_team].cmds[i].inv_pred == true)
                        printf("%4s | ", "yes");
                    else
                        printf("%4s | ", "no");

                    printf("%8s | ", predNames[myTeams[i_team].cmds[i].pred][0].c_str());
                    printf("%7s | ", cmdNames[myTeams[i_team].cmds[i].cmd][0].c_str());
                    printf("%4hu | ", myTeams[i_team].cmds[i].link);
                    printf("[%hu, %hu]", myTeams[i_team].cmds[i].opt[0], myTeams[i_team].cmds[i].opt[1]);
                    printf("\n");
                }
                printf("\n");
            }

        }

        for (int i=0;i<sizeof(myTeams);i++) {
            myTeams->score = 0;
        }


    }

    /*****************************************************************************
    * Function: bool Game::linkColObj(Link myLink, Object myObject)
    * Description: returns true if the link and the object's boxes have collided
    *****************************************************************************/

    bool Game::linkColObj(Link *myLink, Object *myObject) {
        if (!myObject->active) {
            return false;
        }
        uint16_t linkLt = myLink->x;
        uint16_t linkRt = myLink->x + myLink->width;
        uint16_t linkTp = myLink->y + myLink->height;
        uint16_t linkBt = myLink->y;
        uint16_t objLt = myObject->x;
        uint16_t objRt = myObject->x + myObject->width;
        uint16_t objTp = myObject->y + myObject->height;
        uint16_t objBt = myObject->y;
        if ((myLink->direction == DIRECTION_SOUTH)&&((linkLt>objLt && linkLt<objRt)||(linkRt<objRt && linkRt>objLt)) && linkBt<objTp && linkBt> objBt) {
            return true;
        }else
        //heading east
        if ((myLink->direction == DIRECTION_EAST)&&linkRt>objLt && linkRt<objRt && ((linkTp>objBt && linkTp<objTp)||(linkBt>objBt && linkBt<objTp))) {
            return true;
        }else
        //heading west
        if ((myLink->direction == DIRECTION_WEST)&&linkLt>objLt && linkLt<objRt && ((linkTp>objBt && linkTp<objTp)||(linkBt>objBt && linkBt<objTp))) {
            return true;
        }else
        //heading north
        if ((myLink->direction == DIRECTION_NORTH)&&((linkLt>objLt && linkLt<objRt)||(linkRt<objRt && linkRt>objLt)) && linkTp<objTp && linkTp > objBt) {
            return true;
        }
        return false;
    }
    /*****************************************************************************
    * Function: Game::~Game()
    * Description: Destructor for fvu::Game() class
    *****************************************************************************/
    Game::~Game() {
    }

} //namespace foz    test
