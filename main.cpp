//Fuentes:
//http://lazyfoo.net/tutorials/SDL/21_sound_effects_and_music/index.php
//http://content.gpwiki.org/index.php/SDL_mixer:Tutorials:Playing_a_WAV_Sound_File
//Recursos Usados:
//http://soundbible.com/2069-Realistic-Punch.html
//http://3.bp.blogspot.com/_urU_8705ON4/TL8PUxdnsLI/AAAAAAAAA6A/874XiNrkSSM/s1600/fondo-destellos.jpg
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<iostream>
#include<list>
#include <sstream>
#include <SDL2/SDL_mixer.h>  //SE INCLUYE LA LIBRERIA MIXER

using namespace std;
bool success;
Mix_Chunk *Sonido = NULL; //SE DECLARA UN VARIABLE DE TIPO MIX_CHUNK QUE ES LA UTILIZADA PARA SONIDOS

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event Event;
SDL_Texture *background,*game_background, *pelotita_buena, *pelotita_mala, *gameover_background;
SDL_Rect rect_background, rect_pelotita;

void loop_Gameover()
{
    //Main Loop
    while(true)
    {
        while(SDL_PollEvent(&Event))
        {
            if(Event.type == SDL_QUIT)
            {
                exit(0);
            }
            if(Event.type == SDL_KEYDOWN)
            {


        }




        SDL_RenderCopy(renderer, gameover_background, NULL, &rect_background);
        SDL_RenderPresent(renderer);
    }
}
}



void loopJuego()
{

//  list<float>pelotitas_x;
//    pelotitas_x.push_back(0);
//    pelotitas_x.push_back(68);
//    pelotitas_x.push_back(136);
//    pelotitas_x.push_back(204);

    list<float>pelotitas_x;
    pelotitas_x.push_back(0);
    pelotitas_x.push_back(50);
    pelotitas_x.push_back(200);
    pelotitas_x.push_back(300);

     list<float>pelotitas_y;  //Posiciones de la pelotitas en Y en una lista
    pelotitas_y.push_back(0);
    pelotitas_y.push_back(68);
    pelotitas_y.push_back(136);
    pelotitas_y.push_back(204);



    while(true)
    {
        while(SDL_PollEvent(&Event))
        {
            if(Event.type == SDL_QUIT)
            {
                exit(0);
            }
            if(Event.type == SDL_KEYDOWN)
            {
                if(Event.key.keysym.sym == SDLK_ESCAPE)
                    return;
            }
            if(Event.type == SDL_MOUSEBUTTONDOWN)
            {

                int click_x, click_y;
                SDL_GetMouseState( &click_x, &click_y );
                cout<<click_x<<","<<click_y<<endl;

//
//            for(list<float>::iterator i=pelotitas_x.begin();i!=pelotitas_x.end();i++){
//
//                    if(click_x<66+(*i) && click_x>(*i) && click_y<66 && click_y>0)
//                    {
//                        pelotitas_x.erase(i);
//
//                       break;
//
//                    }
//
//            }
//
                try{
                for(list<float>::iterator i=pelotitas_x.begin();i!=pelotitas_x.end();i++){  //se iteran las listas con las posiciones en x
                 for(list<float>::iterator a=pelotitas_y.begin();a!=pelotitas_y.end();a++){ //se iteran la lista con las posiciones en y
                    if(click_x<66+(*i) && click_x>(*i) && click_y<66+(*a) && click_y>0+(*a)) //validacion del click, se activa cuando la posicion x y Y del mouse estan dentro de los limites de las posiciones del valor de la iteracion actual, sumado el tamaño de la figura
                    {
                      //  pelotitas_x.erase(i);
                        pelotitas_y.erase(a); //se elimina la posicion en y para eliminar la pelotita
                        Mix_PlayChannel( -1, Sonido, 0 ); //Se usa esta funcion para reproducir el sonido, el primer argumento se especifica el canal,
                        //el segundo es la variable con el sonido, y el ultimo es la veces q se reproduce
                        throw 0; //utilizo un trow junto con el try catch envez de un break para romper todos los ciclos;

                    }
                }
            }
            }catch(int e){}





            }
        }

        for(list<float>::iterator a=pelotitas_x.begin();
                a!=pelotitas_x.end();
                a++)
        {

            if(pelotitas_y.size()==4){  //mientras la lista contenga cuatro elementos
            (*a)+=0.01;  // se establece esta velocidad al iterador
            rect_pelotita.x=(*a); // se setea la velociadad en el eje x
            }else if(pelotitas_y.size()==3){ //mientras la lista contenga tres elementos
            (*a)+=0.01; // se establece esta velocidad al iterador
            rect_pelotita.x=(*a); // se setea la velociadad en el eje x
            }else if(pelotitas_y.size()==2){ //mientras la lista contenga dos elementos
            (*a)+=0.1; // se establece esta velocidad al iterador
            rect_pelotita.x=(*a); // se setea la velociadad en el eje x
            }else if(pelotitas_y.size()==1){ //mientras la lista contenga un solo elementos
            (*a)+=1; // se establece esta velocidad al iterador
            rect_pelotita.x=(*a); // se setea la velociadad en el eje x
            }



            if((*a)>=500) //cuando la posicion pase del limite
                (*a)=0; //se regresa a su origen
                rect_pelotita.x=(*a);
        }


        if(pelotitas_y.size()==0){ //cuando la lista ya no contiene mas elementos
        loop_Gameover(); //se lanza la pantalla de game over

        }
        SDL_RenderCopy(renderer, game_background, NULL, &rect_background);
//        rect_pelotita.x+=1;
//        if(rect_pelotita.x>=500)
//        rect_pelotita.x=0;


       // SDL_RenderCopy(renderer, pelotita_buena, NULL, &rect_pelotita);

        for(list<float>::iterator i=pelotitas_y.begin();i!=pelotitas_y.end();i++){


            rect_pelotita.y=(*i); //se iteran las pelotitas en y para establecerlas en el eje Y


            SDL_RenderCopy(renderer, pelotita_mala, NULL, &rect_pelotita);

            }

        SDL_RenderPresent(renderer);
    }
}




void loopMenu()
{
    //Main Loop
    while(true)
    {
        while(SDL_PollEvent(&Event))
        {
            if(Event.type == SDL_QUIT)
            {
                exit(0);
            }
            if(Event.type == SDL_KEYDOWN)
            {
                if(Event.key.keysym.sym == SDLK_RETURN)
                    loopJuego();
            }
        }

        SDL_RenderCopy(renderer, background, NULL, &rect_background);
        SDL_RenderPresent(renderer);
    }
}




int main( int argc, char* args[] )
{
    //Init SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return 10;
    }
    //Creates a SDL Window
    if((window = SDL_CreateWindow("Image Loading", 100, 100, 500/*WIDTH*/, 300/*HEIGHT*/, SDL_WINDOW_RESIZABLE | SDL_RENDERER_PRESENTVSYNC)) == NULL)
    {
        return 20;
    }
    //SDL Renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );
    if (renderer == NULL)
    {
        std::cout << SDL_GetError() << std::endl;
        return 30;
    }



    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) //Para inicializar el SDL mixer se necesita llamar la esta funcion,
    //el primer argumento es la frequencia, el segunto el formato, el tercero la cantidad de canales, y el ultimo el tamaño del archivo
    { printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() ); success = false; } //la validacion anterior, imprime
    //un mensaje el mensaje de error en caso que ocurra uno


    //Init textures
    int w=0,h=0;
    background = IMG_LoadTexture(renderer,"assets/menu.png");
    SDL_QueryTexture(background, NULL, NULL, &w, &h);
    rect_background.x = 0;
    rect_background.y = 0;
    rect_background.w = w;
    rect_background.h = h;

    gameover_background = IMG_LoadTexture(renderer,"assets/game_over.png");

    Sonido = Mix_LoadWAV("sound.wav"); //Se Carga el archivo de audio



    game_background = IMG_LoadTexture(renderer,"assets/background.png");

    pelotita_buena = IMG_LoadTexture(renderer,"assets/pelotita_buena.png");
    pelotita_mala = IMG_LoadTexture(renderer,"assets/pelotita_mala.png");

    SDL_QueryTexture(pelotita_buena, NULL, NULL, &rect_pelotita.w, &rect_pelotita.h);
    rect_pelotita.x = 0;
    rect_pelotita.y = 0;


    loopMenu();

	return 0;
}








