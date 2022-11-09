//Projet réalisé par les étudiants MOHAMAN Raïs et KEPSU NJOSSU Jules Algor
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <time.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
int WIDTH=920;
int HEIGHT=700;
int coups=30;

SDL_Texture* loadTexture(char * filename, SDL_Renderer *ren)
{
    SDL_Texture *texture = 0;
    SDL_Surface *loadedImage = 0;
    // Charger une image bmp
    loadedImage = SDL_LoadBMP(filename);
    if (!loadedImage)
    {
        fprintf(stderr,"Erreur chargement image : %s\n",SDL_GetError());
        return 0;
    }
    // Obtenir une texture à partir d'une surface
    texture = SDL_CreateTextureFromSurface(ren, loadedImage);
    // Libérer la surface (plus besoin)
    SDL_FreeSurface(loadedImage);
    if (texture == 0)
    {
        fprintf(stderr,"Erreur creation texture : %s\n",SDL_GetError());
        return 0;
    }
    return texture;
}
void dessin(char * filename,SDL_Renderer * ren)
{
    SDL_Texture * tex = 0;
    SDL_Rect dst;
// Récupérer la texture
    tex = loadTexture(filename,ren);
    if (tex == 0) return;

    // Récupération de la taille de la texture
    SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);

    // Centrage
    dst.x = (WIDTH - dst.w)/2;
    dst.y = (HEIGHT- dst.h)/2;

    // Affichage
    SDL_RenderCopy(ren, tex, NULL, &dst);
    SDL_RenderPresent(ren);
}

struct text
{
    SDL_Texture *tex;
}textu[10],textuf[10],textug[10],textucoups[41];

typedef int Tcarte[11][9];
Tcarte t;

void initialiser() //initialise la matrice de jeu
{
    int i,j;
    for(i=0;i<11;i++)
        for(j=0;j<9;j++)
            t[i][j]=0;
    t[5][1]=1;t[1][7]=1;
    t[1][1]=2;t[5][5]=2;
    t[9][1]=3;t[3][3]=3;
    t[7][1]=4;t[7][7]=4;
    t[1][5]=5;t[3][1]=5;
    t[1][3]=6;t[9][5]=6;
    t[3][7]=7;t[9][7]=7;
    t[9][3]=8;t[5][7]=8;
    t[7][3]=9;t[3][5]=9;
    t[5][3]=10;t[7][5]=10;
}

void zeros() //permet de réinitialiser la matrice lorsque le jeu est fini
{
     int i,j;
    for(i=0;i<11;i++)
        for(j=0;j<9;j++)
            t[i][j]=0;
}
void rando() //permute deux points de manière aléatoire 50 fois pour obtenir une matrice aléatoire
{
    int i,j,c,i1,i2,k;
    for(k=1;k<50;k++)
    {
        do
        {
        i=rand()%10+1;
        j=rand()%10+1;
        i1=rand()%10+1;
        i2=rand()%10+1;
        }while((i%2==0)||(j%2==0)||(j>7)||(i1%2==0)||(i2%2==0)||(i2>7));
        c=t[i][j];
        t[i][j]=t[i1][i2];
        t[i1][i2]=c;
    }
}

void affichejeucons() //affiche la matrice en console
{
    int i,j;
    printf("\n");
    for(i=0; i<9; i++)
    {
        printf("\n");
        for(j=0; j<11; j++)
            printf("%3d",t[j][i]); //%3d pour afficher une image sur 3 caractères
    }
}

int jeufini() //permet de savoir si le jeu est fini ou pas , retourne 0 si toutes les pièces sont découvertes
{
    int i,j,comp=0;
    for(i=0;i<11;i++)
        for(j=0;j<9;j++)
            if((t[i][j]>0))
                comp=1;
    return comp;
}

int jouer(int x1,int y1, int x2, int y2) //prend 2 points en paramètre et met 0 aux valeurs correspondantes si les points sont identiques puis retourne 1, retourne 0 sinon
{
   if(t[x1][y1]==t[x2][y2])
     return 1;
   else
        return 0;

}

void init_graph(SDL_Renderer *ren, SDL_Texture *carre) //permet d'initialiser le plateau avec les cartes retournées et les cartes trouvées
{
    SDL_Rect rect;
    //Recuperation de la taille de la texture
    SDL_QueryTexture(carre, NULL, NULL, &rect.w, &rect.h); //récupère les dimensions de la texture carre
    SDL_RenderClear(ren);
    dessin("backg4.bmp",ren);
    for(int i=0; i<11; i++)
    {
        rect.y=0;
        rect.x=i*rect.w;
        for(int j=0; j<9; j++)
        {
            rect.y=j*rect.h;
            if(t[i][j]>0)
                SDL_RenderCopy(ren,carre,NULL,&rect);
               switch(t[i][j])
           {

                case -1:
                if(t[i][j]==-1)
                    SDL_RenderCopy(ren,textug[0].tex,NULL,&rect);
                   break;
                case -2:
                    SDL_RenderCopy(ren,textug[1].tex,NULL,&rect);
                    break;
                case -3:
                    SDL_RenderCopy(ren,textug[2].tex,NULL,&rect);
                    break;
                case -4:
                    SDL_RenderCopy(ren,textug[3].tex,NULL,&rect);
                    break;
                case -5:
                    SDL_RenderCopy(ren,textug[4].tex,NULL,&rect);
                    break;
                case -6:
                    SDL_RenderCopy(ren,textug[5].tex,NULL,&rect);
                    break;
                case -7:
                    SDL_RenderCopy(ren,textug[6].tex,NULL,&rect);
                    break;
                case -8:
                    SDL_RenderCopy(ren,textug[7].tex,NULL,&rect);
                    break;
                case -9:
                    SDL_RenderCopy(ren,textug[8].tex,NULL,&rect);
                    break;
                 case -10:
                    SDL_RenderCopy(ren,textug[9].tex,NULL,&rect);
                    break;
           }
        }
    }
    SDL_RenderPresent(ren);
}

void affich_graph(SDL_Renderer *ren,SDL_Texture *image, int k,int x1, int y1) //permet d'afficher l'image correspondant à k en un point précis
{
    SDL_Rect rect;
    //Recuperation de la taille de la texture
    SDL_QueryTexture(image, NULL, NULL, &rect.w, &rect.h); //récupère les dimensions de la texture image
    for(int i=0;i<11;i++)
    {
        rect.y=0;
        rect.x=i*rect.w;
        for(int j=0; j<9;j++)
        {
            rect.y=j*rect.h;
            if((t[i][j]==k)&&(i==x1)&&(j==y1))
                SDL_RenderCopy(ren,image,NULL,&rect);
        }
    }
    SDL_RenderPresent(ren);
}

void affiche_graph(SDL_Renderer *ren,int x,int y) //afficher les images en fonction de la valeur contenue dans la matrice
{
    SDL_Rect rect; int k;
    //Recuperation de la taille de la texture
    SDL_QueryTexture(textu[0].tex, NULL, NULL, &rect.w, &rect.h); //récupère les dimensions de la texture image
    for(int i=0;i<11;i++)
    {
        rect.y=0;
        rect.x=i*rect.w;
        for(int j=0; j<9;j++)
        {
            rect.y=j*rect.h;
            if((i==x)&&(j==y))
            {
                k=t[i][j];
                switch(k)
                {
                case 1:
                    SDL_RenderCopy(ren,textu[0].tex,NULL,&rect);
                    break;
                case 2:
                    SDL_RenderCopy(ren,textu[1].tex,NULL,&rect);
                    break;
                case 3:
                    SDL_RenderCopy(ren,textu[2].tex,NULL,&rect);
                    break;
                case 4:
                    SDL_RenderCopy(ren,textu[3].tex,NULL,&rect);
                    break;
                case 5:
                    SDL_RenderCopy(ren,textu[4].tex,NULL,&rect);
                    break;
                case 6:
                    SDL_RenderCopy(ren,textu[5].tex,NULL,&rect);
                    break;
                case 7:
                    SDL_RenderCopy(ren,textu[6].tex,NULL,&rect);
                    break;
                case 8:
                    SDL_RenderCopy(ren,textu[7].tex,NULL,&rect);
                    break;
                case 9:
                    SDL_RenderCopy(ren,textu[8].tex,NULL,&rect);
                    break;
                case 10:
                    SDL_RenderCopy(ren,textu[9].tex,NULL,&rect);
                    break;
                }
            }
        }
    }
    SDL_RenderPresent(ren);
}

void affiche_graph_faux(SDL_Renderer *ren,int x,int y) //affiche les images avec un cadre rouge pour montrer qu'elles ne sont pas bonnes
{
    SDL_Rect rect; int k;
    //Recuperation de la taille de la texture
    SDL_QueryTexture(textu[0].tex, NULL, NULL, &rect.w, &rect.h); //récupère les dimensions de la texture image
    for(int i=0;i<11;i++)
    {
        rect.y=0;
        rect.x=i*rect.w;
        for(int j=0; j<9;j++)
        {
            rect.y=j*rect.h;
            if((i==x)&&(j==y))
            {
                k=t[i][j];
                switch(k)
                {
                case 1:
                    SDL_RenderCopy(ren,textuf[0].tex,NULL,&rect);
                    break;
                case 2:
                    SDL_RenderCopy(ren,textuf[1].tex,NULL,&rect);
                    break;
                case 3:
                    SDL_RenderCopy(ren,textuf[2].tex,NULL,&rect);
                    break;
                case 4:
                    SDL_RenderCopy(ren,textuf[3].tex,NULL,&rect);
                    break;
                case 5:
                    SDL_RenderCopy(ren,textuf[4].tex,NULL,&rect);
                    break;
                case 6:
                    SDL_RenderCopy(ren,textuf[5].tex,NULL,&rect);
                    break;
                case 7:
                    SDL_RenderCopy(ren,textuf[6].tex,NULL,&rect);
                    break;
                case 8:
                    SDL_RenderCopy(ren,textuf[7].tex,NULL,&rect);
                    break;
                case 9:
                    SDL_RenderCopy(ren,textuf[8].tex,NULL,&rect);
                    break;
                case 10:
                    SDL_RenderCopy(ren,textuf[9].tex,NULL,&rect);
                    break;
                }
            }
        }
    }
    SDL_RenderPresent(ren);
}

int main(int argc, char *argv[])
{
    int ewo=0;
    do
    {
    srand(time(NULL));
    int indx1,indy1,indx2,indy2;
    int continuer=0; //pour vérifier le 2e event
    int comptclic=0,comptdif=0; int clicx,clicy,clicx2,clicy2; //pour vérifier si le bouton start est appuyé
    SDL_Renderer *renderer;
    SDL_Rect rectima,rects,rectwat,rectprepa,rectdiff,rectexit,rectre,rectstop; //respectivement : image, bouton start, watermark, prépavogt, bouton difficulté, bouton exit,bouton retry,bouton exit
    initialiser();
    rando();
    affichejeucons();
    SDL_Window *window = NULL;
    int statut = EXIT_FAILURE;
    SDL_Event event,event2,eventcli,eventdif,eventre; //event principal, event du 2e clic, event du bouton start, event de la difficulté, event pour recommencer ou arrêter
    SDL_bool quit= SDL_FALSE;
    SDL_bool quitcli= SDL_FALSE;
    if(0 != SDL_Init(SDL_INIT_VIDEO))
    {
        fprintf(stderr, "Erreur SDL_Init : %s",
                SDL_GetError());
        goto Quit;
    }

    if (0 != SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, SDL_WINDOW_SHOWN, &window, &renderer))
    {
        fprintf(stderr, "erreur SDL_createwindowAndRenderer : %s",SDL_GetError());
    }
    IMG_Init(IMG_INIT_PNG);
    //Les lignes qui suivent correspondent au chargement des textures des images avec un contour vert
    SDL_Surface *image1=IMG_Load("image1g.png");
    textug[0].tex=SDL_CreateTextureFromSurface(renderer,image1);
    textug[1].tex=SDL_CreateTextureFromSurface(renderer,IMG_Load("image2g.png"));
    textug[2].tex=SDL_CreateTextureFromSurface(renderer,IMG_Load("image3g.png"));
    textug[3].tex=SDL_CreateTextureFromSurface(renderer,IMG_Load("image4g.png"));
    textug[4].tex=SDL_CreateTextureFromSurface(renderer,IMG_Load("image5g.png"));
    textug[5].tex=SDL_CreateTextureFromSurface(renderer,IMG_Load("image6g.png"));
    textug[6].tex=SDL_CreateTextureFromSurface(renderer,IMG_Load("image7g.png"));
    textug[7].tex=SDL_CreateTextureFromSurface(renderer,IMG_Load("image8g.png"));
    textug[8].tex=SDL_CreateTextureFromSurface(renderer,IMG_Load("image9g.png"));
    textug[9].tex=SDL_CreateTextureFromSurface(renderer,IMG_Load("image10g.png"));
    //Les lignes qui suivent correspondent au chargement des textures des images
    textu[0].tex=loadTexture("image1.bmp",renderer);
    textu[1].tex=loadTexture("image2.bmp",renderer);
    textu[2].tex=loadTexture("image3.bmp",renderer);
    textu[3].tex=loadTexture("image4.bmp",renderer);
    textu[4].tex=loadTexture("image5.bmp",renderer);
    textu[5].tex=loadTexture("image6.bmp",renderer);
    textu[6].tex=loadTexture("image7.bmp",renderer);
    textu[7].tex=loadTexture("image8.bmp",renderer);
    textu[8].tex=loadTexture("image9.bmp",renderer);
    textu[9].tex=loadTexture("image10.bmp",renderer);
    //Les lignes qui suivent correspondent au chargement des textures des images avec un contour rouge
    textuf[0].tex=loadTexture("image1f.bmp",renderer);
    textuf[1].tex=loadTexture("image2f.bmp",renderer);
    textuf[2].tex=loadTexture("image3f.bmp",renderer);
    textuf[3].tex=loadTexture("image4f.bmp",renderer);
    textuf[4].tex=loadTexture("image5f.bmp",renderer);
    textuf[5].tex=loadTexture("image6f.bmp",renderer);
    textuf[6].tex=loadTexture("image7f.bmp",renderer);
    textuf[7].tex=loadTexture("image8f.bmp",renderer);
    textuf[8].tex=loadTexture("image9f.bmp",renderer);
    textuf[9].tex=loadTexture("image10f.bmp",renderer);
    //Les lignes qui suivent correspondent au chargement des textures des nombres de coups restants
    textucoups[0].tex=SDL_CreateTextureFromSurface(renderer,IMG_Load("nbcoup0.png"));
    textucoups[1].tex=SDL_CreateTextureFromSurface(renderer,IMG_Load("nbcoup1.png"));
    textucoups[2].tex=SDL_CreateTextureFromSurface(renderer,IMG_Load("nbcoup2.png"));
    textucoups[3].tex=SDL_CreateTextureFromSurface(renderer,IMG_Load("nbcoup3.png"));
    textucoups[4].tex=SDL_CreateTextureFromSurface(renderer,IMG_Load("nbcoup4.png"));
    textucoups[5].tex=SDL_CreateTextureFromSurface(renderer,IMG_Load("nbcoup5.png"));
    textucoups[6].tex=SDL_CreateTextureFromSurface(renderer,IMG_Load("nbcoup6.png"));
    textucoups[7].tex=SDL_CreateTextureFromSurface(renderer,IMG_Load("nbcoup7.png"));
    textucoups[8].tex=SDL_CreateTextureFromSurface(renderer,IMG_Load("nbcoup8.png"));
    textucoups[9].tex=SDL_CreateTextureFromSurface(renderer,IMG_Load("nbcoup9.png"));
    textucoups[10].tex=SDL_CreateTextureFromSurface(renderer,IMG_Load("nbcoup10.png"));
    textucoups[11].tex=SDL_CreateTextureFromSurface(renderer,IMG_Load("nbcoup11.png"));
    textucoups[12].tex=SDL_CreateTextureFromSurface(renderer,IMG_Load("nbcoup12.png"));
    textucoups[13].tex=SDL_CreateTextureFromSurface(renderer,IMG_Load("nbcoup13.png"));
    textucoups[14].tex=SDL_CreateTextureFromSurface(renderer,IMG_Load("nbcoup14.png"));
    textucoups[15].tex=SDL_CreateTextureFromSurface(renderer,IMG_Load("nbcoup15.png"));
    textucoups[16].tex=SDL_CreateTextureFromSurface(renderer,IMG_Load("nbcoup16.png"));
    textucoups[17].tex=SDL_CreateTextureFromSurface(renderer,IMG_Load("nbcoup17.png"));
    textucoups[18].tex=SDL_CreateTextureFromSurface(renderer,IMG_Load("nbcoup18.png"));
    textucoups[19].tex=SDL_CreateTextureFromSurface(renderer,IMG_Load("nbcoup19.png"));
    textucoups[20].tex=SDL_CreateTextureFromSurface(renderer,IMG_Load("nbcoup20.png"));
    textucoups[21].tex=SDL_CreateTextureFromSurface(renderer,IMG_Load("nbcoup21.png"));
    textucoups[22].tex=SDL_CreateTextureFromSurface(renderer,IMG_Load("nbcoup22.png"));
    textucoups[23].tex=SDL_CreateTextureFromSurface(renderer,IMG_Load("nbcoup23.png"));
    textucoups[24].tex=SDL_CreateTextureFromSurface(renderer,IMG_Load("nbcoup24.png"));
    textucoups[25].tex=SDL_CreateTextureFromSurface(renderer,IMG_Load("nbcoup25.png"));
    textucoups[26].tex=SDL_CreateTextureFromSurface(renderer,IMG_Load("nbcoup26.png"));
    textucoups[27].tex=SDL_CreateTextureFromSurface(renderer,IMG_Load("nbcoup27.png"));
    textucoups[28].tex=SDL_CreateTextureFromSurface(renderer,IMG_Load("nbcoup28.png"));
    textucoups[29].tex=SDL_CreateTextureFromSurface(renderer,IMG_Load("nbcoup29.png"));
    textucoups[30].tex=SDL_CreateTextureFromSurface(renderer,IMG_Load("nbcoup30.png"));
    textucoups[31].tex=SDL_CreateTextureFromSurface(renderer,IMG_Load("nbcoup31.png"));
    textucoups[32].tex=SDL_CreateTextureFromSurface(renderer,IMG_Load("nbcoup32.png"));
    textucoups[33].tex=SDL_CreateTextureFromSurface(renderer,IMG_Load("nbcoup33.png"));
    textucoups[34].tex=SDL_CreateTextureFromSurface(renderer,IMG_Load("nbcoup34.png"));
    textucoups[35].tex=SDL_CreateTextureFromSurface(renderer,IMG_Load("nbcoup35.png"));
    textucoups[36].tex=SDL_CreateTextureFromSurface(renderer,IMG_Load("nbcoup36.png"));
    textucoups[37].tex=SDL_CreateTextureFromSurface(renderer,IMG_Load("nbcoup37.png"));
    textucoups[38].tex=SDL_CreateTextureFromSurface(renderer,IMG_Load("nbcoup38.png"));
    textucoups[39].tex=SDL_CreateTextureFromSurface(renderer,IMG_Load("nbcoup39.png"));
    textucoups[40].tex=SDL_CreateTextureFromSurface(renderer,IMG_Load("nbcoup40.png"));
    //Les lignes qui suivent correspondent à l'initialisation des textures de la 1ere page
    SDL_Texture *texexit=SDL_CreateTextureFromSurface(renderer,IMG_Load("exit.png")); //texture bouton exit
    SDL_Texture *carre = loadTexture("groscarre.bmp",renderer); //texture retournee du carré. groscarre mesure du 85x85.
    SDL_Texture *texo= SDL_CreateTextureFromSurface(renderer,IMG_Load("memory.png")); //texture image de fond
    SDL_Texture *texwat =SDL_CreateTextureFromSurface(renderer,IMG_Load("watermark2.png")); //texture watermark
    SDL_Texture *texs=loadTexture("startbutton.bmp",renderer); //texture bouton start
    SDL_Texture *texprepa=SDL_CreateTextureFromSurface(renderer,IMG_Load("prepa.png")); //texture prépavogt
    SDL_Texture *texdiff=SDL_CreateTextureFromSurface(renderer,IMG_Load("difficulty.png")); //texture bouton difficulté
    SDL_Texture *texre=SDL_CreateTextureFromSurface(renderer,IMG_Load("retry.png"));
    //Les lignes qui suivent correspondent à l'initialisation des rectangles nécessaires pour la 1ère page
    rectima.w= WIDTH; rectima.h=HEIGHT;
    rectima.x = (WIDTH - rectima.w)/2;
    rectima.y = (HEIGHT- rectima.h)/2;
    SDL_RenderCopy(renderer, texo, NULL, &rectima); //affichage fond décran
    SDL_QueryTexture(texs, NULL, NULL, &rects.w, &rects.h);
    rects.x=365;
    rects.y=600;
    SDL_QueryTexture(texwat,NULL,NULL,&rectwat.w,&rectwat.h);
    rectwat.x=700;
    rectwat.y=40;
    SDL_RenderCopy(renderer,texs, NULL, &rects); //affichage bouton start
    SDL_RenderCopy(renderer,texwat,NULL,&rectwat); //affichage watermark
    SDL_QueryTexture(texprepa,NULL,NULL,&rectprepa.w,&rectprepa.h);
    rectprepa.x=40;
    rectprepa.y=20;
    SDL_QueryTexture(texdiff,NULL,NULL,&rectdiff.w,&rectdiff.h);
    rectdiff.x=40;
    rectdiff.y=600;
    SDL_QueryTexture(texexit,NULL,NULL,&rectexit.w,&rectexit.h);
    rectexit.x=680;
    rectexit.y=600;
    SDL_QueryTexture(texre,NULL,NULL,&rectre.w,&rectre.h);
    rectre.x=60;
    rectre.y=600;
    SDL_RenderCopy(renderer, texexit, NULL, &rectexit); //affichage bouton exit
    SDL_RenderCopy(renderer,texprepa,NULL,&rectprepa); //affichage logo prépavogt
    SDL_RenderCopy(renderer,texdiff,NULL,&rectdiff); //affichage bouton de difficulté
    SDL_RenderPresent(renderer);
     while(comptclic==0)
    {
        SDL_WaitEvent(&eventcli);
        comptdif=0;
        if(eventcli.type == SDL_QUIT)
            quitcli = SDL_TRUE;
        else if(eventcli.type == SDL_MOUSEBUTTONUP)
        {
            if(eventcli.button.button == SDL_BUTTON_LEFT)
            {
                clicx=eventcli.button.x;
                clicy=eventcli.button.y;
                printf("%d - %d\n",clicx,clicy);
                if((clicx>=rects.x)&&(clicx<=rects.x+rects.w))
                    if((clicy>=rects.y)&&(clicy<=rects.y+rects.h)) //Si le bouton start est appuyé :
                    {
                        comptclic=1;
                        SDL_RenderClear(renderer);
                        SDL_RenderPresent(renderer);//On efface le rendu et on passe à la suite du programme
                    }
                if((clicx>=rectdiff.x)&&(clicx<=rectdiff.x+rectdiff.w))
                    if((clicy>=rectdiff.y)&&(clicy<=rectdiff.y+rectdiff.h)) //Si le bouton Game difficulty est appuyé :
                    {
                        SDL_RenderClear(renderer);
                        SDL_RenderPresent(renderer);
                        SDL_Rect recteasy,rectmed,recthard,rectins,rectfond; //rectangles correspondant aux différentes difficultés
                        SDL_Texture *texeasy,*texmed,*texhard,*texins,*texfond; //textures associées
                        texfond=SDL_CreateTextureFromSurface(renderer,IMG_Load("fond.png"));
                        texeasy=SDL_CreateTextureFromSurface(renderer,IMG_Load("easy.png"));
                        texmed=SDL_CreateTextureFromSurface(renderer,IMG_Load("medium.png"));
                        texhard=SDL_CreateTextureFromSurface(renderer,IMG_Load("hard.png"));
                        texins=SDL_CreateTextureFromSurface(renderer,IMG_Load("insane.png"));
                        //Les lignes qui suivent correspondent à l'initialisation des rectangles
                        rectfond.w=WIDTH; rectfond.h=HEIGHT;
                        rectfond.x = (WIDTH - rectfond.w)/2;
                        rectfond.y = (HEIGHT- rectfond.h)/2;
                        SDL_QueryTexture(texeasy,NULL,NULL,&recteasy.w,&recteasy.h);
                        recteasy.x=148; recteasy.y=190;
                        SDL_QueryTexture(texmed,NULL,NULL,&rectmed.w,&rectmed.h);
                        rectmed.x=594; rectmed.y=190;
                        SDL_QueryTexture(texhard,NULL,NULL,&recthard.w,&recthard.h);
                        recthard.x=148; recthard.y=513;
                        SDL_QueryTexture(texins,NULL,NULL,&rectins.w,&rectins.h);
                        rectins.x=594; rectins.y=513;
                        SDL_RenderCopy(renderer,texfond,NULL,&rectfond);
                        SDL_RenderCopy(renderer,texeasy,NULL,&recteasy);
                        SDL_RenderCopy(renderer,texmed,NULL,&rectmed);
                        SDL_RenderCopy(renderer,texhard,NULL,&recthard);
                        SDL_RenderCopy(renderer,texins,NULL,&rectins);
                        SDL_RenderPresent(renderer); //Affichage des boutons de difficulté
                        while(comptdif==0)
                        {
                            SDL_WaitEvent(&eventdif);
                            if (eventdif.type== SDL_MOUSEBUTTONUP)
                                if(eventdif.button.button == SDL_BUTTON_LEFT)
                                    {
                                       comptdif++;
                                       clicx2=eventdif.button.x;
                                       clicy2=eventdif.button.y;
                                        if((clicx2>=recteasy.x)&&(clicx2<=recteasy.x+recteasy.w)&&(clicy2>=recteasy.y)&&(clicy2<=recteasy.y+recteasy.h)) //Si easy est appuyé
                                               coups=40;
                                        else if((clicx2>=rectmed.x)&&(clicx2<=rectmed.x+rectmed.w)&&(clicy2>=rectmed.y)&&(clicy2<=rectmed.y+rectmed.h)) //Si medium est appuyé
                                               coups=30;
                                        else if((clicx2>=recthard.x)&&(clicx2<=recthard.x+recthard.w)&&(clicy2>=recthard.y)&&(clicy2<=recthard.y+recthard.h)) //Si hard est appuyé
                                                coups=20;
                                        else if((clicx2>=rectins.x)&&(clicx2<=rectins.x+rectins.w)&&(clicy2>=rectins.y)&&(clicy2<=rectins.y+rectins.h)) //Si ??? est appuyé
                                                coups=10;
                                    SDL_RenderClear(renderer); //On nettoie le rendu et on affiche à nouveau la 1ère page
                                    SDL_RenderCopy(renderer, texo, NULL, &rectima);
                                     SDL_RenderCopy(renderer, texexit, NULL, &rectexit);
                                    SDL_RenderCopy(renderer,texprepa,NULL,&rectprepa);
                                    SDL_RenderCopy(renderer,texdiff,NULL,&rectdiff);
                                    SDL_RenderCopy(renderer,texs, NULL, &rects);
                                    SDL_RenderCopy(renderer,texwat,NULL,&rectwat);
                                    SDL_RenderPresent(renderer);
                                    }
                        }
                    }
                if((clicx>=rectexit.x)&&(clicx<=rectexit.x+rectexit.w))
                    if((clicy>=rectexit.y)&&(clicy<=rectexit.y+rectexit.h)) //Si le bouton Exit est appuyé
                    {
                        SDL_RenderClear(renderer);
                        SDL_RenderPresent(renderer);
                        comptclic=1;
                        quit=SDL_TRUE;
                        ewo=1;
                    }
            }
        }
    }
    init_graph(renderer,carre);
    int coup1=coups; SDL_Rect rectcoup;
    if(coups==0)
    {
        coups=30;
        coup1=30;
    }
    SDL_QueryTexture(textucoups[40].tex,NULL,NULL,&rectcoup.w,&rectcoup.h);
    rectcoup.x=328;
    rectcoup.y=40;
    while(!quit)
    {
        continuer=0;
    if(coups==40) //Si easy est sélectionné
        {
            SDL_RenderCopy(renderer,textucoups[40].tex,NULL,&rectcoup);
            SDL_RenderPresent(renderer);
        }
    if(coups==30) //Si medium est sélectionné
        {
            SDL_RenderCopy(renderer,textucoups[30].tex,NULL,&rectcoup);
            SDL_RenderPresent(renderer);
        }
    if(coups==20) //Si hard est sélectionné
        {
            SDL_RenderCopy(renderer,textucoups[20].tex,NULL,&rectcoup);
            SDL_RenderPresent(renderer);
        }
    if(coups==10) //Si ??? est sélectionné
        {
            SDL_RenderCopy(renderer,textucoups[10].tex,NULL,&rectcoup);
            SDL_RenderPresent(renderer);
        }
        SDL_WaitEvent(&event); //Attente du 1er clic
        if(event.type == SDL_QUIT)
        {
            ewo=1; quit = SDL_TRUE;
        }
        else if(event.type == SDL_MOUSEBUTTONUP)
        {
            if(event.button.button == SDL_BUTTON_LEFT)
            {
                indx1 = event.button.x/85;
                indy1 = event.button.y/85;
               affiche_graph(renderer,indx1,indy1); //retourne la 1ère image
                while(continuer==0)
                {
                     SDL_WaitEvent(&event2); //Attente du 2e clic
                     if(event2.type == SDL_QUIT)
                        quit = SDL_TRUE;
                else if(event2.type == SDL_MOUSEBUTTONUP)
                    if(event2.button.button == SDL_BUTTON_LEFT)
                    {
                             continuer++;
                              indx2=  event2.button.x/85;
                            indy2 = event2.button.y/85;
                             affiche_graph(renderer,indx2,indy2); //retourne la 2e image et sort de la boucle while
                    }

                }
                indx1 = event.button.x/85;
                indy1 = event.button.y/85;
                indx2=  event2.button.x/85;
                indy2 = event2.button.y/85;
                if((jouer(indx1,indy1,indx2,indy2)==1)&&((indx1!=indx2)||(indy1!=indy2)))
                        {
                            t[indx1][indy1]*=-1;
                            t[indx2][indy2]*=-1;
                        }
                else if(jouer(indx1,indy1,indx2,indy2)==0)
                        {
                            affiche_graph_faux(renderer,indx1,indy1);
                            affiche_graph_faux(renderer,indx2,indy2);//met un cadre rouge sur les 2 images puis on les fera clignoter
                            SDL_Delay(200);
                            init_graph(renderer,carre);
                            SDL_Delay(100);
                            affiche_graph_faux(renderer,indx1,indy1);
                            affiche_graph_faux(renderer,indx2,indy2);
                            SDL_Delay(300);
                            init_graph(renderer,carre);
                        }
                    SDL_RenderClear(renderer);
                    init_graph(renderer,carre);
                    if((indx1%2==0)||(indx2%2==0)||(indy1%2==0)||(indy2%2==0))
                        coups++;
                    coups--;  //diminue le nombre de coups
                     switch(coups) //affiche le nombre de coups restants
                        {
                        case 39:
                            SDL_RenderCopy(renderer,textucoups[39].tex,NULL,&rectcoup);
                            break;
                        case 38:
                            SDL_RenderCopy(renderer,textucoups[38].tex,NULL,&rectcoup);
                            break;
                        case 37:
                            SDL_RenderCopy(renderer,textucoups[37].tex,NULL,&rectcoup);
                            break;
                        case 36:
                            SDL_RenderCopy(renderer,textucoups[36].tex,NULL,&rectcoup);
                            break;
                        case 35:
                            SDL_RenderCopy(renderer,textucoups[35].tex,NULL,&rectcoup);
                            break;
                        case 34:
                            SDL_RenderCopy(renderer,textucoups[34].tex,NULL,&rectcoup);
                            break;
                        case 33:
                            SDL_RenderCopy(renderer,textucoups[33].tex,NULL,&rectcoup);
                            break;
                        case 32:
                            SDL_RenderCopy(renderer,textucoups[32].tex,NULL,&rectcoup);
                            break;
                        case 31:
                            SDL_RenderCopy(renderer,textucoups[31].tex,NULL,&rectcoup);
                            break;
                        case 30:
                            SDL_RenderCopy(renderer,textucoups[30].tex,NULL,&rectcoup);
                            break;
                        case 29:
                            SDL_RenderCopy(renderer,textucoups[29].tex,NULL,&rectcoup);
                            break;
                        case 28:
                            SDL_RenderCopy(renderer,textucoups[28].tex,NULL,&rectcoup);
                            break;
                        case 27:
                            SDL_RenderCopy(renderer,textucoups[27].tex,NULL,&rectcoup);
                            break;
                        case 26:
                            SDL_RenderCopy(renderer,textucoups[26].tex,NULL,&rectcoup);
                            break;
                        case 25:
                            SDL_RenderCopy(renderer,textucoups[25].tex,NULL,&rectcoup);
                            break;
                        case 24:
                            SDL_RenderCopy(renderer,textucoups[24].tex,NULL,&rectcoup);
                            break;
                        case 23:
                            SDL_RenderCopy(renderer,textucoups[23].tex,NULL,&rectcoup);
                            break;
                        case 22:
                            SDL_RenderCopy(renderer,textucoups[22].tex,NULL,&rectcoup);
                            break;
                        case 21:
                            SDL_RenderCopy(renderer,textucoups[21].tex,NULL,&rectcoup);
                            break;
                        case 20:
                            SDL_RenderCopy(renderer,textucoups[20].tex,NULL,&rectcoup);
                            break;
                        case 19:
                            SDL_RenderCopy(renderer,textucoups[19].tex,NULL,&rectcoup);
                            break;
                        case 18:
                            SDL_RenderCopy(renderer,textucoups[18].tex,NULL,&rectcoup);
                            break;
                        case 17:
                            SDL_RenderCopy(renderer,textucoups[17].tex,NULL,&rectcoup);
                            break;
                        case 16:
                            SDL_RenderCopy(renderer,textucoups[16].tex,NULL,&rectcoup);
                            break;
                        case 15:
                            SDL_RenderCopy(renderer,textucoups[15].tex,NULL,&rectcoup);
                            break;
                        case 14:
                            SDL_RenderCopy(renderer,textucoups[14].tex,NULL,&rectcoup);
                            break;
                        case 13:
                            SDL_RenderCopy(renderer,textucoups[13].tex,NULL,&rectcoup);
                            break;
                        case 12:
                            SDL_RenderCopy(renderer,textucoups[12].tex,NULL,&rectcoup);
                            break;
                        case 11:
                            SDL_RenderCopy(renderer,textucoups[11].tex,NULL,&rectcoup);
                            break;
                        case 10:
                            SDL_RenderCopy(renderer,textucoups[10].tex,NULL,&rectcoup);
                            break;
                        case 9:
                            SDL_RenderCopy(renderer,textucoups[9].tex,NULL,&rectcoup);
                            break;
                        case 8:
                            SDL_RenderCopy(renderer,textucoups[8].tex,NULL,&rectcoup);
                            break;
                        case 7:
                            SDL_RenderCopy(renderer,textucoups[7].tex,NULL,&rectcoup);
                            break;
                        case 6:
                            SDL_RenderCopy(renderer,textucoups[6].tex,NULL,&rectcoup);
                            break;
                        case 5:
                            SDL_RenderCopy(renderer,textucoups[5].tex,NULL,&rectcoup);
                            break;
                        case 4:
                            SDL_RenderCopy(renderer,textucoups[4].tex,NULL,&rectcoup);
                            break;
                        case 3:
                            SDL_RenderCopy(renderer,textucoups[3].tex,NULL,&rectcoup);
                            break;
                        case 2:
                            SDL_RenderCopy(renderer,textucoups[2].tex,NULL,&rectcoup);
                            break;
                        case 1:
                            SDL_RenderCopy(renderer,textucoups[1].tex,NULL,&rectcoup);
                            break;
                        case 0:
                            SDL_RenderCopy(renderer,textucoups[0].tex,NULL,&rectcoup);
                            break;
                        }
                    SDL_RenderPresent(renderer);
                    affichejeucons();
                     SDL_Delay(300);
                    }
                    if((coups==0)&&(jeufini()!=0))
                    {
                          SDL_RenderClear(renderer);
                          zeros();
                          init_graph(renderer,carre);
                          dessin("gameover.bmp",renderer);
                          t[5][1]=2; //pour ne pas entrer dans jeufini
                          int still=0;
                          SDL_RenderCopy(renderer, texexit, NULL, &rectexit);
                          SDL_RenderPresent(renderer);
                          while(still==0)
                          {
                              SDL_WaitEvent(&eventre);
                              if(eventre.type == SDL_MOUSEBUTTONUP)
                                    if(eventre.button.button == SDL_BUTTON_LEFT)
                                        {
                                            int re1=eventre.button.x;
                                            int re2=eventre.button.y;
                                            if((re1>=rectexit.x)&&(re1<=rectexit.x+rectexit.w)&&(re2>=rectexit.y)&&(re2<=rectexit.y+rectexit.h)) //Si le bouton Exit est appuyé
                                            {
                                                SDL_RenderClear(renderer);
                                                SDL_RenderPresent(renderer);
                                                comptclic=1;
                                                quit=SDL_TRUE;
                                                ewo=1;
                                                still=1;
                                            }
                                            else
                                            {
                                                still=1;
                                                quit=SDL_TRUE;
                                                SDL_RenderClear(renderer);
                                            }
                                        }
                          }
                          coups=coup1;
                        }
                    if(jeufini()==0)
                    {
                          SDL_RenderClear(renderer);
                          zeros();
                          init_graph(renderer,carre);
                         dessin("you win.bmp",renderer);
                         coups=coup1;
                         quit=SDL_TRUE;
                         int still=0;
                          SDL_RenderCopy(renderer, texexit, NULL, &rectexit);
                          SDL_RenderPresent(renderer);
                          while(still==0)
                          {
                              SDL_WaitEvent(&eventre);
                              if(eventre.type == SDL_MOUSEBUTTONUP)
                                    if(eventre.button.button == SDL_BUTTON_LEFT)
                                        {
                                            int re1=eventre.button.x;
                                            int re2=eventre.button.y;
                                            if((re1>=rectexit.x)&&(re1<=rectexit.x+rectexit.w)&&(re2>=rectexit.y)&&(re2<=rectexit.y+rectexit.h)) //Si le bouton Exit est appuyé
                                            {
                                                SDL_RenderClear(renderer);
                                                SDL_RenderPresent(renderer);
                                                comptclic=1;
                                                quit=SDL_TRUE;
                                                ewo=1;
                                                still=1;
                                            }
                                            else
                                            {
                                                still=1;
                                                quit=SDL_TRUE;
                                                SDL_RenderClear(renderer);
                                            }
                                        }
                          }
                    }

        }

        else if(event.type == SDL_KEYDOWN) //si on appuie sur echap, la fenêtre est détruite
        {
            if(event.key.keysym.sym == SDLK_ESCAPE)
            {
                quit = SDL_TRUE; ewo=1;
            }

        }
        SDL_Delay(20);
    }
    Quit:
    SDL_Quit();
    IMG_Quit();
    }while(ewo==0);
    return 0;
}
