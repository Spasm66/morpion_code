#include <SDL.h>
#include <SDL/SDL_image.h>
#include <SDL_ttf.h>

void    click(int x, int y, int *row, int *col);
int     board(int **plat,int x, int y, int forme);
int     is_win(int **plat);

int     main(void)
{
    SDL_Init(SDL_INIT_VIDEO);
    if (IMG_Init(IMG_INIT_JPG) == 0)
    {
        fprintf(stderr, "Erreur lors de l'initialisation de SDL_image : %s\n", IMG_GetError());
        return 1;
    }
    TTF_Init();
    SDL_Surface *window;
    SDL_Surface *ver;
    SDL_Surface *hor;
    SDL_Surface *croix;
    SDL_Surface *rond;
    SDL_Surface *refresh;
    SDL_Surface *text;
    SDL_Rect    ver_pos;
    SDL_Rect    hor_pos;
    SDL_Rect    pos;
    int         **plat;
    int         current_row;
    int         current_col;

    TTF_Font *arial;
    arial = TTF_OpenFont("retro.ttf", 180);
    if (arial == NULL)
    {
        fprintf(stderr, "Error opening font: %s\n", TTF_GetError());
        return (1);
    }
    window = SDL_SetVideoMode(800, 800, 32, SDL_HWSURFACE);
    SDL_FillRect(window, NULL, SDL_MapRGB(window -> format, 0, 50, 90));
    ver = SDL_CreateRGBSurface(SDL_HWSURFACE, 5, 600, 32, 0, 0, 0, 0);
    SDL_FillRect(ver, NULL, SDL_MapRGB(window -> format, 0, 0, 0));
    hor = SDL_CreateRGBSurface(SDL_HWSURFACE, 600, 5, 32, 0, 0, 0, 0);
    SDL_FillRect(hor, NULL, SDL_MapRGB(window -> format, 0, 0, 0));
    refresh = SDL_CreateRGBSurface(SDL_HWSURFACE, 800, 800, 32, 0, 0, 0, 0);
    SDL_FillRect(refresh, NULL, SDL_MapRGB(window -> format, 0, 50, 90));
    croix = IMG_Load("croix.jpg");
    SDL_Color font_color = {0, 0, 0, 0};
    text = TTF_RenderText_Solid(arial, "w0n", font_color);
    if (croix == NULL)
    {
        fprintf(stderr, "Erreur lors du chargement de l'image : %s\n", IMG_GetError());
        return 1;
    }
    rond = IMG_Load("rond.jpg");
    if (rond == NULL)
    {
        fprintf(stderr, "Erreur lors du chargement de l'image : %s\n", IMG_GetError());
        return 1;
    }
    ver_pos.x = 300;
    ver_pos.y = 100;
    SDL_BlitSurface(ver, NULL, window, &ver_pos);
    ver_pos.x = 500;
    ver_pos.y = 100;
    SDL_BlitSurface(ver, NULL, window, &ver_pos);
    hor_pos.x = 100;
    hor_pos.y = 300;
    SDL_BlitSurface(hor, NULL, window, &hor_pos);
    hor_pos.x = 100;
    hor_pos.y = 500; 
    SDL_BlitSurface(hor, NULL, window, &hor_pos);
    SDL_Flip(window);
    
    plat = malloc(sizeof(int*) * 3);
    if(!plat)
    {
        free(plat);
        return (1);
    }
    for (int i = 0; i < 3; i++)
    {
        plat[i] = calloc(3, sizeof(int));;
        if (!plat[i])
        {
            for (int j = 0; j < i; j++)
                free(plat[j]);
            free(plat);
            return(1);
        }
    }

    plat = malloc(sizeof(int*) * 3);
    if(!plat)
    {
        free(plat);
        return (1);
    }
    for (int i = 0; i < 3; i++)
    {
        plat[i] = calloc(3, sizeof(int));;
        if (!plat[i])
        {
            for (int j = 0; j < i; j++)
                free(plat[j]);
            free(plat);
            return(1);
        }
    }
    SDL_Event   event;
    int         player;
    player = 1;
    while(!is_win(plat))
    {
        SDL_WaitEvent(&event);
        if (event.type == SDL_QUIT)
            break;
        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                click(event.button.x, event.button.y, &current_col, &current_row);
                if (board(plat, current_col, current_row, player) == 1)
                {
                    pos.x = 110 + current_row * 200;
                    pos.y = 110 + current_col * 200;
                    if (player == 1)
                        SDL_BlitSurface(croix, NULL, window, &pos);
                    else if (player == 2)
                        SDL_BlitSurface(rond, NULL, window, &pos);
                    SDL_Flip(window);
                    player ^= 3;
                }
            }
        }
    }
    SDL_Rect    re_pos;
    re_pos.x = 0;
    re_pos.y = 0;
    while (is_win(plat))
    {
        SDL_WaitEvent(&event);
        if (event.type == SDL_QUIT)
            break;
        SDL_BlitSurface(refresh, NULL, window, &re_pos);
        pos.x = 150;
        pos.y = 300;
        if (is_win(plat) == 1)
            SDL_BlitSurface(croix, NULL, window, &pos);
        if (is_win(plat) == 2)
            SDL_BlitSurface(rond, NULL, window, &pos);
        pos.x = 380;
        pos.y = 315;
        SDL_BlitSurface(text, NULL, window, &pos);
        SDL_Flip(window);
    }
    SDL_FreeSurface(window);
    SDL_Quit();
}
