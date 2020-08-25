#include <iostream>
#include <allegro.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
using namespace std;

/*  SPRITES GUARDADOS

SOMBRA MISTERIOSA
	masked_blit(sombra_misteriosa,buffer,0,0,16,126,452,201); /// Mostrar Sombra Misteriosa

ESQUELETO GUERRERO
	masked_blit(esqueleto_guerrero,buffer,0,0,470,190,132,96); /// Mostrar Esqueleto Guerrero

MERCADER
	masked_blit(mercader,buffer,0,0,100,126,357,201); /// Mostrar Mercader

BOTIN
	masked_blit(botin,buffer,0,0,180,240,121,70); /// Mostrar Botin

LAPIDA CURATIVA
	masked_blit(lapida_curativa,buffer,0,0,180,220,117,98); /// Mostrar Lapida Curativa

COFRE MISTERIOSO
	masked_blit(cofre_misterioso,buffer,0,0,180,240,157,100); /// Mostrar Cofre Misterioso

ESQUELETO GUERRERO POSICION 1
	masked_blit(esqueleto_guerrero,buffer,0,0,85,210,132,96);

ESQUELETO GUERRERO POSICION 2
	masked_blit(esqueleto_guerreroMarcado,buffer,0,0,245,140,132,146);

*/

// Estructura que guarda los datos del personaje
struct Personaje {
    int vida;
    int mana;
    int ataque;
    int defensa;
    int pociones;
    int oro;
} pj;

// Estructura que guarda la vida de los enemigos
struct Enemigos {
    int vida; // Vida del enemio
    int barra_vida; // Barra de vida que se ve
    int danio; // Danio del enemigo
    int defensa; // Defensa del enemigo
} esqueleto;

/////////////////////////////////////////////// FUNCION PRINCIPAL

int main() {
    /// Cosas de Allegro ///
    allegro_init(); // Inicializar Allegro
    install_keyboard(); // Para que se pueda usar comandos de teclado
    install_mouse(); // Para que se pueda usar el mouse
    set_color_depth(32); // Usar colores 32 bits
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640,480, 0,0); // Definir el tamanio de la ventana
    BITMAP *buffer = create_bitmap(640,480); // Crear el fondo de la ventana
    BITMAP *fondo = load_bitmap(".\\Imagenes\\Fondo.bmp",NULL); // Cargar fondo
    BITMAP *fondo0 = load_bitmap(".\\Imagenes\\Fondo0.bmp",NULL); // Cargar fondo
    BITMAP *vida = load_bitmap(".\\Imagenes\\Vida.bmp",NULL); // Cargar barra de Vida
    BITMAP *mana = load_bitmap(".\\Imagenes\\Mana.bmp",NULL); // Cargar barra de Mana
    BITMAP *cursor = load_bitmap(".\\Imagenes\\cursor.bmp",NULL); // Cargar barra de Mana
    BITMAP *Batacar = load_bitmap(".\\Imagenes\\Batacar.bmp",NULL); // Cargar Resaltar boton Atacar
    BITMAP *Bdefender = load_bitmap(".\\Imagenes\\Bdefender.bmp",NULL); // Cargar Resaltar boton Defender
    BITMAP *Busarpocion = load_bitmap(".\\Imagenes\\Busarpocion.bmp",NULL); // Cargar Resaltar boton Usar pocion
    BITMAP *Bavanzar = load_bitmap(".\\Imagenes\\Bavanzar.bmp",NULL); // Cargar Resaltar boton Avanzar
    BITMAP *BotonR_verdeB = load_bitmap(".\\Imagenes\\BRverdeB.bmp", NULL); // Cargar Boton R Verde Blanco
    BITMAP *BotonR_rojoB = load_bitmap(".\\Imagenes\\BRrojoB.bmp", NULL); // Cargar Boton R Rojo Blanco
    BITMAP *BotonR_rojoN = load_bitmap(".\\Imagenes\\BRrojoN.bmp", NULL); // Cargar Boton R Rojo Negro
    BITMAP *BotonR_azulB = load_bitmap(".\\Imagenes\\BRazulB.bmp", NULL); // Cargar Boton R Rojo Negro
    /// Cosas del Stage 1 Zonas[1,20]///
    BITMAP *stage1 = load_bitmap(".\\Imagenes\\Stage1.bmp",NULL); // Cargar fondo del Stage 1 Zona [1,20]
    BITMAP *esqueleto_guerrero = load_bitmap(".\\Imagenes\\EsqueletoGuerrero.bmp",NULL); // Cargar Esqueleto Guerrero
    BITMAP *esqueleto_guerreroMarcado = load_bitmap(".\\Imagenes\\EsqueletoMarcado.bmp",NULL); // Cargar Esqueleto Guerrero Marcado
    BITMAP *sombra_misteriosa = load_bitmap(".\\Imagenes\\SombraMisteriosa.bmp",NULL); // Cargar Sombra Misteriosa
    BITMAP *mercader = load_bitmap(".\\Imagenes\\Mercader.bmp",NULL); // Cargar Mercader
    BITMAP *mercader_precio = load_bitmap(".\\Imagenes\\MercaderPrecio.bmp",NULL); // Cargar cartel de precios
    BITMAP *botin = load_bitmap(".\\Imagenes\\Botin.bmp", NULL); // Cargar Botin
    BITMAP *fragua = load_bitmap(".\\Imagenes\\Fragua.bmp", NULL); // Cargar Fragua
    BITMAP *lapida_curativa = load_bitmap(".\\Imagenes\\Lapida.bmp", NULL); // Cargar Fragua
    BITMAP *cofre_misterioso = load_bitmap(".\\Imagenes\\CofreMisterioso.bmp", NULL); // Cargar Cofre Misterioso
    BITMAP *marco_vidaEsqueleto = load_bitmap(".\\Imagenes\\MarcoVidaEsqueleto.bmp", NULL); // Cargar Marco de vida del esqueleto
    BITMAP *vida_enemigo = load_bitmap(".\\Imagenes\\VidaEnemigo.bmp", NULL); // Cargar barra de vida del enemigo

/////////////////////////////////////////////// VARIABLES DEL JUEGO

    /// Cosas normales ///
    // Valores iniciales del personaje
    pj.vida = 100;
    pj.mana = 100;
    pj.ataque = 1;
    pj.defensa = 0;
    pj.pociones = 0;
    pj.oro = 0;

    int zona (0); // Controlador de Zonas
    bool avanzar; // Controlador boton R
    srand(time(NULL)); // Iniciar generador de numero aleatorio
    int n_evento; // Decide que evento se activara con un numero aleatorio
    bool evento; // Controlar cuando sucede un evento

/////////////////////////////////////////////// COMIENZO DEL JUEGO

    while (!key[KEY_ESC]) {

        // Mostrar pantalla principal
        blit(buffer,screen,0,0,0,0,640,480);
        blit(fondo,buffer,0,0,0,0, 640,480); // Fondo principal del juego
        blit(vida,buffer,0,0,28,28,pj.vida,29); // Barra de Vida
        blit(mana,buffer,0,0,28,70,pj.mana,29); // Barra de Mana
        // Mostrar datos pantalla principal
        textprintf_ex(buffer, font, 100, 32, makecol(0, 0, 0),-1, "%d", pj.vida); // Mostrar Vida
        textprintf_ex(buffer, font, 100, 74, makecol(0, 0, 0),-1, "%d", pj.mana); // Mostrar Mana
        textprintf_ex(buffer, font, 310, 42, makecol(0, 0, 0),-1, "%d", pj.ataque); // Mostrar Ataque
        textprintf_ex(buffer, font, 315, 85, makecol(0, 0, 0),-1, "%d", pj.defensa); // Mostrar Defensa
        textprintf_ex(buffer, font, 460, 42, makecol(0, 0, 0),-1, "%d", pj.pociones); // Mostrar Pociones
        textprintf_ex(buffer, font, 425, 85, makecol(230, 236, 16),-1, "%d", pj.oro); // Mostrar Oro
        textprintf_ex(buffer, font, 590, 366, makecol(0, 0, 0),-1, "%d", zona); // Mostrar Zona

////////// ZONA 0 - Inspeccion de controles ///
        if (zona == 0) {
            avanzar = true;
            blit(fondo0, buffer, 0,0,0,126,453,201); /// Mostrar Fondo0 (relleno negro)
            blit(BotonR_azulB,buffer,0,0,482,368,34,27); // Mostrar Boton R Rojo Blanco
            textout_ex(buffer,font,"== NECRO DUNGEON ==",473,146,makecol(255, 255, 255), -1);
            textout_ex(buffer,font,"Pasa el cursor sobre",463,176,makecol(255, 255, 255), -1);
            textout_ex(buffer,font,"las opciones para ver",463,195,makecol(255, 255, 255), -1);
            textout_ex(buffer,font,"que hacen",463,214,makecol(255, 255, 255), -1);
            /// Resaltar opciones con el mouse ///

            if ((mouse_x >= 28 && mouse_x <= 154) && (mouse_y >= 354 && mouse_y <= 395)) { /// Resaltar boton Atacar
                blit(Batacar,buffer,0,0,28,354,127,42);
                textout_ex(buffer,font,"Haces dano igual a tu ataque",20,176,makecol(255, 255, 255), -1);
                textout_ex(buffer,font,"(varia segun la defensa del enemigo)",20,195,makecol(255, 255, 255), -1);
            } else if ((mouse_x >= 28 && mouse_x <= 154) && (mouse_y >= 410 && mouse_y <= 451)) { /// Resaltar boton Defender
                blit(Bdefender,buffer,0,0,28,410,127,42);
                textout_ex(buffer,font,"Reduces el dano recibido a la mitad",20,176,makecol(255, 255, 255), -1);
                textout_ex(buffer,font,"Desactivado durante los niveles 1-20",20,195,makecol(255, 255, 255), -1);
            } else if ((mouse_x >= 184 && mouse_x <= 310) && (mouse_y >= 354 && mouse_y <= 395)) { /// Resaltar boton Usar pocion
                blit(Busarpocion,buffer,0,0,184,354,127,42);
                textout_ex(buffer,font,"Recuperas 20 puntos de vida",20,176,makecol(255, 255, 255), -1);
            } else if (((mouse_x >= 184 && mouse_x <= 310) && (mouse_y >= 410 && mouse_y <= 451)) ||
                       ((mouse_x >= 340 && mouse_x <= 467) && (mouse_y >= 354 && mouse_y <= 394)) ||
                       ((mouse_x >= 340 && mouse_x <= 466) && (mouse_y >= 410 && mouse_y <= 451))) { /// Resaltaron botones ???
                textout_ex(buffer,font,"Habilidades desbloqueadas al derrotar un jefe",20,176,makecol(255, 255, 255), -1);
                textout_ex(buffer,font,"Los jefes se encuentran cada 20 niveles",20,195,makecol(255, 255, 255), -1);
                textout_ex(buffer,font,"Hay 5 jefes en total",20,274,makecol(255, 255, 255), -1);
            } else if ((mouse_x >= 524 && mouse_x <= 623) && (mouse_y >= 354 && mouse_y <= 382)) { /// Resaltar boton Zona
                textout_ex(buffer,font,"Muestra la zona actual en la que te encuentras",20,176,makecol(255, 255, 255), -1);
            } else if ((mouse_x >= 25 && mouse_x <= 130) && (mouse_y >= 25 && mouse_y <= 59)) { /// Resaltar Vida
                textout_ex(buffer,font,"Muestra cuanta vida te queda",20,176,makecol(255, 255, 255), -1);
            } else if ((mouse_x >= 25 && mouse_x <= 130) && (mouse_y >= 67 && mouse_y <= 101)) { /// Resaltar Mana
                textout_ex(buffer,font,"Muestra cuanto mana te queda",20,176,makecol(255, 255, 255), -1);
                textout_ex(buffer,font,"Se utiliza para usar las habilidades",20,195,makecol(255, 255, 255), -1);
            } else if ((mouse_x >= 241 && mouse_x <= 353) && (mouse_y >= 28 && mouse_y <= 56)) { /// Resaltar Ataque
                textout_ex(buffer,font,"Muestra tu ataque actual",20,176,makecol(255, 255, 255), -1);
                textout_ex(buffer,font,"Entre mas ataque tengas mas dano haces",20,195,makecol(255, 255, 255), -1);
                textout_ex(buffer,font,"La defensa del enemigo reduce el dano causado",20,214,makecol(255, 255, 255), -1);
                textout_ex(buffer,font,"5% chances de golpe critico que cause doble dano",20,233,makecol(255, 255, 255), -1);
            } else if ((mouse_x >= 241 && mouse_x <= 353) && (mouse_y >= 71 && mouse_y <= 99)) { /// Resaltar Defensa
                textout_ex(buffer,font,"Reduce el dano recibido por el enemigo",20,176,makecol(255, 255, 255), -1);
            } else if ((mouse_x >= 381 && mouse_x <= 493) && (mouse_y >= 27 && mouse_y <= 55)) { /// Resaltar Pociones
                textout_ex(buffer,font,"Muestra la cantidad de pociones que posees",20,176,makecol(255, 255, 255), -1);
                textout_ex(buffer,font,"Puedes usar pociones para curarte 20 de vida",20,195,makecol(255, 255, 255), -1);
            } else if ((mouse_x >= 381 && mouse_x <= 493) && (mouse_y >= 70 && mouse_y <= 98)) { /// Resaltar Oro
                textout_ex(buffer,font,"Muestra la cantidad de oro que posees",20,176,makecol(255, 255, 255), -1);
                textout_ex(buffer,font,"Puedes usar el oro para comprar en las tiendas",20,195,makecol(255, 255, 255), -1);
            } else if ((mouse_x >= 525 && mouse_x <= 623) && (mouse_y >= 17 && mouse_y <= 113)) { /// Cuadrado misterioso
                textout_ex(buffer,font,"Se desbloquea en una zona alta...",20,176,makecol(255, 255, 255), -1);
            } else if ((mouse_x >= 453 && mouse_x <= 639) && (mouse_y >= 126 && mouse_y <= 326)) { /// Cuandro de texto
                textout_ex(buffer,font,"Muestra la informacion de lo que suceda",20,176,makecol(255, 255, 255), -1);
            } else if ((mouse_x >= 482 && mouse_x <= 516) && (mouse_y >= 368 && mouse_y <= 395)) { /// Boton R Azul
                textout_ex(buffer,font,"Al seleccionar una de las 6 acciones disponibles",20,176,makecol(255, 255, 255), -1);
                textout_ex(buffer,font,"este boton se pondra rojo y se bloquearan las opciones",20,195,makecol(255, 255, 255), -1);
                textout_ex(buffer,font,"Deberas pulsarlo para poder seleccionar otra accion",20,214,makecol(255, 255, 255), -1);
            } else if ((mouse_x >= 482 && mouse_x <= 516) && (mouse_y >= 424 && mouse_y <= 451)) { /// Boton R Verde
                textout_ex(buffer,font,"Al avanzar de zona este boton se volvera rojo",20,176,makecol(255, 255, 255), -1);
                textout_ex(buffer,font,"Debes tener el boton en verde para avanzar de zona",20,195,makecol(255, 255, 255), -1);
                textout_ex(buffer,font,"En algunas ocasiones se pondra verde automaticamente",20,214,makecol(255, 255, 255), -1);
            }

            if (avanzar == true) {
                blit(BotonR_verdeB,buffer,0,0,482,424,34,27); /// Mostrar Boton R Verde Blanco
                if ((mouse_x >= 524 && mouse_x <= 623) && (mouse_y >= 424 && mouse_y <= 451)) { /// Resaltar boton Avanzar
                    blit(Bavanzar,buffer,0,0,524,424,100,27);
                    textout_ex(buffer,font,"Avanzas de zona",20,176,makecol(255, 255, 255), -1);
                    textout_ex(buffer,font,"Presiona para comenzar la partida",20,195,makecol(255, 255, 255), -1);
                    if (mouse_b & 1) { /// Si se hace click se desactiva el boton Avanzar
                        zona++;
                        avanzar = false;
                    }
                }
            }
        }

////////// ZONA 1-19 - Stage 1///
        if (zona >= 1 && zona <= 19) {
            n_evento = 1+rand()%100; // Numero aleatorio [1,100] para controlar porcentaje
            evento = true;

            /// SOMBRA MISTERIOSA ///
            if (n_evento == 1) { // 1% chances de que aparezca una Sombra Misteriosa
                int turno(1);
                bool accionar = true; // Controlador de acciones Boton R Azul

                do {
                    /// ACTIVAR EFECTO UNA SOLA VEZ ///
                    bool efecto;
                    if (turno == 1) {
                        efecto = true;
                    }
                    if (efecto == true) {
                        pj.pociones /= 2;
                        pj.oro /= 2;
                        efecto = false;
                        turno++;
                    }

                    // Mostrar pantalla principal
                    blit(buffer,screen,0,0,0,0,640,480);
                    blit(fondo,buffer,0,0,0,0, 640,480); // Fondo principal del juego
                    blit(vida,buffer,0,0,28,28,pj.vida,29); // Barra de Vida
                    blit(mana,buffer,0,0,28,70,pj.mana,29); // Barra de Mana
                    blit(stage1, buffer, 0,0,0,126,453,201); /// Mostrar Stage 1
                    // Mostrar datos pantalla principal
                    textprintf_ex(buffer, font, 100, 32, makecol(0, 0, 0),-1, "%d", pj.vida); // Mostrar Vida
                    textprintf_ex(buffer, font, 100, 74, makecol(0, 0, 0),-1, "%d", pj.mana); // Mostrar Mana
                    textprintf_ex(buffer, font, 310, 42, makecol(0, 0, 0),-1, "%d", pj.ataque); // Mostrar Ataque
                    textprintf_ex(buffer, font, 315, 85, makecol(0, 0, 0),-1, "%d", pj.defensa); // Mostrar Defensa
                    textprintf_ex(buffer, font, 460, 42, makecol(0, 0, 0),-1, "%d", pj.pociones); // Mostrar Pociones
                    textprintf_ex(buffer, font, 425, 85, makecol(230, 236, 16),-1, "%d", pj.oro); // Mostrar Oro
                    textprintf_ex(buffer, font, 590, 366, makecol(0, 0, 0),-1, "%d", zona); // Mostrar Zona

                    /// BOTON R AZUL PARA ACCIONES ///
                    if (accionar == false) {
                        blit(BotonR_rojoB,buffer,0,0,482,368,34,27); // Mostrar Boton R Rojo Blanco
                        if ((mouse_x >= 482 && mouse_x <= 516) && (mouse_y >= 368 && mouse_y <= 395)) { // Resaltar boton Avanzar
                            blit(BotonR_rojoN,buffer,0,0,482,368,34,27);
                            textout_ex(buffer, font, "Habilitar acciones", 30, 460, makecol(255, 255, 255), -1);
                            if (mouse_b & 1) { // Si se hace click se desactiva el boton Avanzar
                                accionar = true;
                            }
                        }
                    } else if (accionar == true) {
                        blit(BotonR_azulB,buffer,0,0,482,368,34,27); // Mostrar Boton R Rojo Blanco
                    }
                    /// USAR POCIONES ///
                    if ((mouse_x >= 184 && mouse_x <= 310) && (mouse_y >= 354 && mouse_y <= 395)) { // Resaltar boton Usar pocion
                        blit(Busarpocion,buffer,0,0,184,354,127,42);
                        textout_ex(buffer,font,"Recuperas 20 puntos de vida",30,460,makecol(255, 255, 255), -1);
                        if (mouse_b & 1) { // Al hacer clic
                            if ((accionar == true) && (pj.pociones > 0)) {
                                if (pj.vida < 100) {
                                    pj.pociones -= 1;
                                    if (pj.vida >= 80) {
                                        pj.vida = 100;
                                        accionar = false;
                                    } else if (pj.vida < 80) {
                                        pj.vida += 20;
                                        accionar = false;
                                    }
                                }
                            }
                        }
                    }

                    masked_blit(sombra_misteriosa,buffer,0,0,16,126,452,201); // Mostrar Sombra Misteriosa

                    textout_ex(buffer,font,"TE HAS TOPADO CON UNA",462,158,makecol(255, 255, 255), -1); // Mostrar mensaje de encuentro
                    textout_ex(buffer,font,"SOMBRA MISTERIOSA",472,172,makecol(255, 255, 255), -1);

                    textout_ex(buffer,font,"Pierdes la mitad de",468,202,makecol(255, 255, 255), -1); // Mostrar efecto
                    textout_ex(buffer,font,"tus pociones y oro",468,215,makecol(255, 255, 255), -1);

                    /// BOTON AVANZAR ///
                    if (avanzar == true) {
                        blit(BotonR_verdeB,buffer,0,0,482,424,34,27); /// Mostrar Boton R Verde Blanco
                        if ((mouse_x >= 524 && mouse_x <= 623) && (mouse_y >= 424 && mouse_y <= 451)) { /// Resaltar boton Avanzar
                            blit(Bavanzar,buffer,0,0,524,424,100,27);
                            textout_ex(buffer, font, "Avanzar a la siguiente zona", 30, 460, makecol(255, 255, 255), -1);
                            if (mouse_b & 1) { /// Si se hace click se desactiva el boton Avanzar
                                zona++;
                                avanzar = false;
                                evento = false;
                            }
                        }
                    } else if (avanzar == false) {
                        blit(BotonR_rojoB,buffer,0,0,482,424,34,27); /// Mostrar Boton R Rojo Blanco
                        if ((mouse_x >= 482 && mouse_x <= 517) && (mouse_y >= 424 && mouse_y <= 451)) { /// Resaltar Boton R Rojo Blanco
                            blit(BotonR_rojoN,buffer,0,0,482,424,34,27); /// Mostrar Boton R Rojo Negro
                            textout_ex(buffer, font, "Activar boton Avanzar", 30, 460, makecol(255, 255, 255), -1);
                            if (mouse_b & 1) {
                                avanzar = true;
                            }
                        }
                    }
                    masked_blit(cursor,buffer,0,0,mouse_x,mouse_y,13,22); // Mostrar cursor
                } while ((evento == true) && (!key[KEY_ESC]));
            }

            /// FRAGUA ///
            else if (n_evento > 1 && n_evento <= 3) { // 2% chances de que aparezca una Sombra Misteriosa
                int turno(1);
                int efecto_aleatorio = 1+rand()%100; // Numero aleatorio [1.100]
                int aumento = 1+rand()%5; // Numero aleatorio [1,5]
                bool accionar = true; // Controlador de acciones Boton R Azul

                do {
                    /// ACTIVAR EFECTO UNA SOLA VEZ /

                    bool efecto;
                    if (turno == 1) {
                        efecto = true;
                    }
                    if (efecto == true) {
                        if (efecto_aleatorio <= 50) { // Aumentar ataque
                            pj.ataque += aumento;
                        } else if (efecto_aleatorio > 50) { // Aumentar defensa
                            pj.defensa += aumento;
                        }
                        efecto = false;
                        turno++;
                    }

                    if (efecto_aleatorio <= 50) { // 50% chances de mejorar el ataque 1-5
                        textprintf_ex(buffer, font, 462, 202, makecol(255, 255, 255),-1, "+ %d", aumento); // Mostrar efecto
                        textout_ex(buffer, font, "Ataque", 492, 202, makecol(255, 255, 255), -1);
                    } else if (efecto_aleatorio > 50) { // 50% chances de mejorar la defensa 1-5
                        textprintf_ex(buffer, font, 462, 202, makecol(255, 255, 255),-1, "+ %d", aumento); // Mostrar efecto
                        textout_ex(buffer, font, "Defensa", 492, 202, makecol(255, 255, 255), -1);
                    }

                    // Mostrar pantalla principal
                    blit(buffer,screen,0,0,0,0,640,480);
                    blit(fondo,buffer,0,0,0,0, 640,480); // Fondo principal del juego
                    blit(vida,buffer,0,0,28,28,pj.vida,29); // Barra de Vida
                    blit(mana,buffer,0,0,28,70,pj.mana,29); // Barra de Mana
                    blit(stage1, buffer, 0,0,0,126,453,201); /// Mostrar Stage 1
                    // Mostrar datos pantalla principal
                    textprintf_ex(buffer, font, 100, 32, makecol(0, 0, 0),-1, "%d", pj.vida); // Mostrar Vida
                    textprintf_ex(buffer, font, 100, 74, makecol(0, 0, 0),-1, "%d", pj.mana); // Mostrar Mana
                    textprintf_ex(buffer, font, 310, 42, makecol(0, 0, 0),-1, "%d", pj.ataque); // Mostrar Ataque
                    textprintf_ex(buffer, font, 315, 85, makecol(0, 0, 0),-1, "%d", pj.defensa); // Mostrar Defensa
                    textprintf_ex(buffer, font, 460, 42, makecol(0, 0, 0),-1, "%d", pj.pociones); // Mostrar Pociones
                    textprintf_ex(buffer, font, 425, 85, makecol(230, 236, 16),-1, "%d", pj.oro); // Mostrar Oro
                    textprintf_ex(buffer, font, 590, 366, makecol(0, 0, 0),-1, "%d", zona); // Mostrar Zona

                    /// BOTON R AZUL PARA ACCIONES ///
                    if (accionar == false) {
                        blit(BotonR_rojoB,buffer,0,0,482,368,34,27); // Mostrar Boton R Rojo Blanco
                        if ((mouse_x >= 482 && mouse_x <= 516) && (mouse_y >= 368 && mouse_y <= 395)) { // Resaltar boton Avanzar
                            blit(BotonR_rojoN,buffer,0,0,482,368,34,27);
                            textout_ex(buffer, font, "Habilitar acciones", 30, 460, makecol(255, 255, 255), -1);
                            if (mouse_b & 1) { // Si se hace click se desactiva el boton Avanzar
                                accionar = true;
                            }
                        }
                    } else if (accionar == true) {
                        blit(BotonR_azulB,buffer,0,0,482,368,34,27); // Mostrar Boton R Rojo Blanco
                    }
                    /// USAR POCIONES ///
                    if ((mouse_x >= 184 && mouse_x <= 310) && (mouse_y >= 354 && mouse_y <= 395)) { // Resaltar boton Usar pocion
                        blit(Busarpocion,buffer,0,0,184,354,127,42);
                        textout_ex(buffer,font,"Recuperas 20 puntos de vida",30,460,makecol(255, 255, 255), -1);
                        if (mouse_b & 1) { // Al hacer clic
                            if ((accionar == true) && (pj.pociones > 0)) {
                                if (pj.vida < 100) {
                                    pj.pociones -= 1;
                                    if (pj.vida >= 80) {
                                        pj.vida = 100;
                                        accionar = false;
                                    } else if (pj.vida < 80) {
                                        pj.vida += 20;
                                        accionar = false;
                                    }
                                }
                            }
                        }
                    }

                    masked_blit(fragua,buffer,0,0,40,140,339,181); // Mostrar Sombra Misteriosa

                    textout_ex(buffer,font,"HAS ENCONTRADO UNA",462,158,makecol(255, 255, 255), -1); // Mostrar mensaje de encuentro
                    textout_ex(buffer,font,"FRAGUA",462,172,makecol(255, 255, 255), -1);


                    /// BOTON AVANZAR ///
                    if (avanzar == true) {
                        blit(BotonR_verdeB,buffer,0,0,482,424,34,27); /// Mostrar Boton R Verde Blanco
                        if ((mouse_x >= 524 && mouse_x <= 623) && (mouse_y >= 424 && mouse_y <= 451)) { /// Resaltar boton Avanzar
                            blit(Bavanzar,buffer,0,0,524,424,100,27);
                            textout_ex(buffer, font, "Avanzar a la siguiente zona", 30, 460, makecol(255, 255, 255), -1);
                            if (mouse_b & 1) { /// Si se hace click se desactiva el boton Avanzar
                                zona++;
                                avanzar = false;
                                evento = false;
                            }
                        }
                    } else if (avanzar == false) {
                        blit(BotonR_rojoB,buffer,0,0,482,424,34,27); /// Mostrar Boton R Rojo Blanco
                        if ((mouse_x >= 482 && mouse_x <= 517) && (mouse_y >= 424 && mouse_y <= 451)) { /// Resaltar Boton R Rojo Blanco
                            blit(BotonR_rojoN,buffer,0,0,482,424,34,27); /// Mostrar Boton R Rojo Negro
                            textout_ex(buffer, font, "Activar boton Avanzar", 30, 460, makecol(255, 255, 255), -1);
                            if (mouse_b & 1) {
                                avanzar = true;
                            }
                        }
                    }
                    masked_blit(cursor,buffer,0,0,mouse_x,mouse_y,13,22); // Mostrar cursor
                } while ((evento == true) && (!key[KEY_ESC]));
            }

            /// BOTIN ///
            else if (n_evento > 3 && n_evento <= 9) { // 6% chances de que aparezca un BOTIN
                int turno(1);
                int aumento_oro = 20+rand()%31; // Numero aleatorio [20,50]
                bool accionar = true; // Controlador de acciones Boton R Azul

                do {
                    /// ACTIVAR EFECTO UNA SOLA VEZ ///
                    bool efecto;
                    if (turno == 1) {
                        efecto = true;
                    }
                    if (efecto == true) {
                        pj.oro += aumento_oro; // Activar efecto
                        efecto = false;
                        turno++;
                    }

                    // Mostrar pantalla principal
                    blit(buffer,screen,0,0,0,0,640,480);
                    blit(fondo,buffer,0,0,0,0, 640,480); // Fondo principal del juego
                    blit(vida,buffer,0,0,28,28,pj.vida,29); // Barra de Vida
                    blit(mana,buffer,0,0,28,70,pj.mana,29); // Barra de Mana
                    blit(stage1, buffer, 0,0,0,126,453,201); /// Mostrar Stage 1
                    // Mostrar datos pantalla principal
                    textprintf_ex(buffer, font, 100, 32, makecol(0, 0, 0),-1, "%d", pj.vida); // Mostrar Vida
                    textprintf_ex(buffer, font, 100, 74, makecol(0, 0, 0),-1, "%d", pj.mana); // Mostrar Mana
                    textprintf_ex(buffer, font, 310, 42, makecol(0, 0, 0),-1, "%d", pj.ataque); // Mostrar Ataque
                    textprintf_ex(buffer, font, 315, 85, makecol(0, 0, 0),-1, "%d", pj.defensa); // Mostrar Defensa
                    textprintf_ex(buffer, font, 460, 42, makecol(0, 0, 0),-1, "%d", pj.pociones); // Mostrar Pociones
                    textprintf_ex(buffer, font, 425, 85, makecol(230, 236, 16),-1, "%d", pj.oro); // Mostrar Oro
                    textprintf_ex(buffer, font, 590, 366, makecol(0, 0, 0),-1, "%d", zona); // Mostrar Zona

                    /// BOTON R AZUL PARA ACCIONES ///
                    if (accionar == false) {
                        blit(BotonR_rojoB,buffer,0,0,482,368,34,27); // Mostrar Boton R Rojo Blanco
                        if ((mouse_x >= 482 && mouse_x <= 516) && (mouse_y >= 368 && mouse_y <= 395)) { // Resaltar boton Avanzar
                            blit(BotonR_rojoN,buffer,0,0,482,368,34,27);
                            textout_ex(buffer, font, "Habilitar acciones", 30, 460, makecol(255, 255, 255), -1);
                            if (mouse_b & 1) { // Si se hace click se desactiva el boton Avanzar
                                accionar = true;
                            }
                        }
                    } else if (accionar == true) {
                        blit(BotonR_azulB,buffer,0,0,482,368,34,27); // Mostrar Boton R Rojo Blanco
                    }
                    /// USAR POCIONES ///
                    if ((mouse_x >= 184 && mouse_x <= 310) && (mouse_y >= 354 && mouse_y <= 395)) { // Resaltar boton Usar pocion
                        blit(Busarpocion,buffer,0,0,184,354,127,42);
                        textout_ex(buffer,font,"Recuperas 20 puntos de vida",30,460,makecol(255, 255, 255), -1);
                        if (mouse_b & 1) { // Al hacer clic
                            if ((accionar == true) && (pj.pociones > 0)) {
                                if (pj.vida < 100) {
                                    pj.pociones -= 1;
                                    if (pj.vida >= 80) {
                                        pj.vida = 100;
                                        accionar = false;
                                    } else if (pj.vida < 80) {
                                        pj.vida += 20;
                                        accionar = false;
                                    }
                                }
                            }
                        }
                    }

                    masked_blit(botin,buffer,0,0,180,240,121,70); /// Mostrar Botin

                    textout_ex(buffer,font,"HAS ENCONTRADO UN",462,158,makecol(255, 255, 255), -1); // Mostrar mensaje de encuentro
                    textout_ex(buffer,font,"BOTIN",462,172,makecol(255, 255, 255), -1);

                    textprintf_ex(buffer, font, 462, 202, makecol(255, 255, 255),-1, "+ %d", aumento_oro); // Mostrar efecto
                    textout_ex(buffer, font, "de Oro", 500, 202, makecol(255, 255, 255), -1);

                    /// BOTON AVANZAR ///
                    if (avanzar == true) {
                        blit(BotonR_verdeB,buffer,0,0,482,424,34,27); /// Mostrar Boton R Verde Blanco
                        if ((mouse_x >= 524 && mouse_x <= 623) && (mouse_y >= 424 && mouse_y <= 451)) { /// Resaltar boton Avanzar
                            blit(Bavanzar,buffer,0,0,524,424,100,27);
                            textout_ex(buffer, font, "Avanzar a la siguiente zona", 30, 460, makecol(255, 255, 255), -1);
                            if (mouse_b & 1) { /// Si se hace click se desactiva el boton Avanzar
                                zona++;
                                avanzar = false;
                                evento = false;
                            }
                        }
                    } else if (avanzar == false) {
                        blit(BotonR_rojoB,buffer,0,0,482,424,34,27); /// Mostrar Boton R Rojo Blanco
                        if ((mouse_x >= 482 && mouse_x <= 517) && (mouse_y >= 424 && mouse_y <= 451)) { /// Resaltar Boton R Rojo Blanco
                            blit(BotonR_rojoN,buffer,0,0,482,424,34,27); /// Mostrar Boton R Rojo Negro
                            textout_ex(buffer, font, "Activar boton Avanzar", 30, 460, makecol(255, 255, 255), -1);
                            if (mouse_b & 1) {
                                avanzar = true;
                            }
                        }
                    }
                    masked_blit(cursor,buffer,0,0,mouse_x,mouse_y,13,22); // Mostrar cursor
                } while ((evento == true) && (!key[KEY_ESC]));
            }

            /// LAPIDA CURATIVA ///
            else if (n_evento > 9 && n_evento <= 15) { // 6% chances de que aparezca una LAPIDA CURATIVA
                int turno(1);
                int mensaje; // (1= < 50), (2 >= 50), (3 = 100)
                int vida_recuperada; // Vida recuperada si vida >= 100
                bool accionar = true; // Controlador de acciones Boton R Azul

                do {
                    /// ACTIVAR EFECTO UNA SOLA VEZ ///
                    bool efecto;
                    if (turno == 1) {
                        efecto = true;
                    }
                    if (efecto == true) {
                        if (pj.vida == 100) {
                            pj.vida = 100;
                            mensaje = 1;
                        } else if (pj.vida >= 50 && pj.vida < 100) {
                            vida_recuperada = 100 - pj.vida; // Cantidad de vida recuperada
                            pj.vida = 100;
                            mensaje = 2;
                        } else if (pj.vida < 50) {
                            pj.vida += 50;
                            mensaje = 3;
                        }
                        efecto = false;
                        turno++;
                    }

                    // Mostrar pantalla principal
                    blit(buffer,screen,0,0,0,0,640,480);
                    blit(fondo,buffer,0,0,0,0, 640,480); // Fondo principal del juego
                    blit(vida,buffer,0,0,28,28,pj.vida,29); // Barra de Vida
                    blit(mana,buffer,0,0,28,70,pj.mana,29); // Barra de Mana
                    blit(stage1, buffer, 0,0,0,126,453,201); /// Mostrar Stage 1
                    // Mostrar datos pantalla principal
                    textprintf_ex(buffer, font, 100, 32, makecol(0, 0, 0),-1, "%d", pj.vida); // Mostrar Vida
                    textprintf_ex(buffer, font, 100, 74, makecol(0, 0, 0),-1, "%d", pj.mana); // Mostrar Mana
                    textprintf_ex(buffer, font, 310, 42, makecol(0, 0, 0),-1, "%d", pj.ataque); // Mostrar Ataque
                    textprintf_ex(buffer, font, 315, 85, makecol(0, 0, 0),-1, "%d", pj.defensa); // Mostrar Defensa
                    textprintf_ex(buffer, font, 460, 42, makecol(0, 0, 0),-1, "%d", pj.pociones); // Mostrar Pociones
                    textprintf_ex(buffer, font, 425, 85, makecol(230, 236, 16),-1, "%d", pj.oro); // Mostrar Oro
                    textprintf_ex(buffer, font, 590, 366, makecol(0, 0, 0),-1, "%d", zona); // Mostrar Zona

                    /// BOTON R AZUL PARA ACCIONES ///
                    if (accionar == false) {
                        blit(BotonR_rojoB,buffer,0,0,482,368,34,27); // Mostrar Boton R Rojo Blanco
                        if ((mouse_x >= 482 && mouse_x <= 516) && (mouse_y >= 368 && mouse_y <= 395)) { // Resaltar boton Avanzar
                            blit(BotonR_rojoN,buffer,0,0,482,368,34,27);
                            textout_ex(buffer, font, "Habilitar acciones", 30, 460, makecol(255, 255, 255), -1);
                            if (mouse_b & 1) { // Si se hace click se desactiva el boton Avanzar
                                accionar = true;
                            }
                        }
                    } else if (accionar == true) {
                        blit(BotonR_azulB,buffer,0,0,482,368,34,27); // Mostrar Boton R Rojo Blanco
                    }
                    /// USAR POCIONES ///
                    if ((mouse_x >= 184 && mouse_x <= 310) && (mouse_y >= 354 && mouse_y <= 395)) { // Resaltar boton Usar pocion
                        blit(Busarpocion,buffer,0,0,184,354,127,42);
                        textout_ex(buffer,font,"Recuperas 20 puntos de vida",30,460,makecol(255, 255, 255), -1);
                        if (mouse_b & 1) { // Al hacer clic
                            if ((accionar == true) && (pj.pociones > 0)) {
                                if (pj.vida < 100) {
                                    pj.pociones -= 1;
                                    if (pj.vida >= 80) {
                                        pj.vida = 100;
                                        accionar = false;
                                    } else if (pj.vida < 80) {
                                        pj.vida += 20;
                                        accionar = false;
                                    }
                                }
                            }
                        }
                    }

                    masked_blit(lapida_curativa,buffer,0,0,180,220,117,98); /// Mostrar Lapida Curativa

                    textout_ex(buffer,font,"HAS ENCONTRADO UNA",462,158,makecol(255, 255, 255), -1); // Mostrar mensaje de encuentro
                    textout_ex(buffer,font,"LAPIDA CURATIVA",462,172,makecol(255, 255, 255), -1);

                    textout_ex(buffer, font, "Lees el conjuro", 462, 202, makecol(255, 255, 255), -1);

                    if (mensaje == 1) { // Mensaje vida al maximo
                        textout_ex(buffer, font, "La vida ya esta", 462, 232, makecol(255, 255, 255), -1);
                        textout_ex(buffer, font, "al maximo", 462, 245, makecol(255, 255, 255), -1);
                    } else if (mensaje == 2) { // Mensaje vida >= 50
                        textprintf_ex(buffer, font, 462, 232, makecol(255, 255, 255),-1, "Has recuperado %d", vida_recuperada); // Mostrar Zona
                        textout_ex(buffer, font, "puntos de vida", 462, 245, makecol(255, 255, 255), -1);
                    } else if (mensaje == 3) { // Mensaje vida < 50
                        textout_ex(buffer, font, "Has recuperado 50", 462, 232, makecol(255, 255, 255), -1);
                        textout_ex(buffer, font, "puntos de vida", 462, 245, makecol(255, 255, 255), -1);
                    }

                    /// BOTON AVANZAR ///
                    if (avanzar == true) {
                        blit(BotonR_verdeB,buffer,0,0,482,424,34,27); /// Mostrar Boton R Verde Blanco
                        if ((mouse_x >= 524 && mouse_x <= 623) && (mouse_y >= 424 && mouse_y <= 451)) { /// Resaltar boton Avanzar
                            blit(Bavanzar,buffer,0,0,524,424,100,27);
                            textout_ex(buffer, font, "Avanzar a la siguiente zona", 30, 460, makecol(255, 255, 255), -1);
                            if (mouse_b & 1) { /// Si se hace click se desactiva el boton Avanzar
                                zona++;
                                avanzar = false;
                                evento = false;
                            }
                        }
                    } else if (avanzar == false) {
                        blit(BotonR_rojoB,buffer,0,0,482,424,34,27); /// Mostrar Boton R Rojo Blanco
                        if ((mouse_x >= 482 && mouse_x <= 517) && (mouse_y >= 424 && mouse_y <= 451)) { /// Resaltar Boton R Rojo Blanco
                            blit(BotonR_rojoN,buffer,0,0,482,424,34,27); /// Mostrar Boton R Rojo Negro
                            textout_ex(buffer, font, "Activar boton Avanzar", 30, 460, makecol(255, 255, 255), -1);
                            if (mouse_b & 1) {
                                avanzar = true;
                            }
                        }
                    }
                    masked_blit(cursor,buffer,0,0,mouse_x,mouse_y,13,22); // Mostrar cursor
                } while ((evento == true) && (!key[KEY_ESC]));
            }

            /// MERCADER ///
            else if (n_evento > 15 && n_evento <= 35) { // 20% chances de que aparezca un MERCADER
                int turno(1);
                bool accionar = true; // Controlador de acciones Boton R Azul

                do {
                    // Mostrar pantalla principal
                    blit(buffer,screen,0,0,0,0,640,480);
                    blit(fondo,buffer,0,0,0,0, 640,480); // Fondo principal del juego
                    blit(vida,buffer,0,0,28,28,pj.vida,29); // Barra de Vida
                    blit(mana,buffer,0,0,28,70,pj.mana,29); // Barra de Mana
                    blit(stage1, buffer, 0,0,0,126,453,201); // Mostrar Stage 1
                    // Mostrar datos pantalla principal
                    textprintf_ex(buffer, font, 100, 32, makecol(0, 0, 0),-1, "%d", pj.vida); // Mostrar Vida
                    textprintf_ex(buffer, font, 100, 74, makecol(0, 0, 0),-1, "%d", pj.mana); // Mostrar Mana
                    textprintf_ex(buffer, font, 310, 42, makecol(0, 0, 0),-1, "%d", pj.ataque); // Mostrar Ataque
                    textprintf_ex(buffer, font, 315, 85, makecol(0, 0, 0),-1, "%d", pj.defensa); // Mostrar Defensa
                    textprintf_ex(buffer, font, 460, 42, makecol(0, 0, 0),-1, "%d", pj.pociones); // Mostrar Pociones
                    textprintf_ex(buffer, font, 425, 85, makecol(230, 236, 16),-1, "%d", pj.oro); // Mostrar Oro
                    textprintf_ex(buffer, font, 590, 366, makecol(0, 0, 0),-1, "%d", zona); // Mostrar Zona

                    /// BOTON R AZUL PARA ACCIONES ///
                    if (accionar == false) {
                        blit(BotonR_rojoB,buffer,0,0,482,368,34,27); // Mostrar Boton R Rojo Blanco
                        if ((mouse_x >= 482 && mouse_x <= 516) && (mouse_y >= 368 && mouse_y <= 395)) { // Resaltar boton Avanzar
                            blit(BotonR_rojoN,buffer,0,0,482,368,34,27);
                            textout_ex(buffer, font, "Habilitar acciones", 30, 460, makecol(255, 255, 255), -1);
                            if (mouse_b & 1) { // Si se hace click se desactiva el boton Avanzar
                                accionar = true;
                            }
                        }
                    } else if (accionar == true) {
                        blit(BotonR_azulB,buffer,0,0,482,368,34,27); // Mostrar Boton R Rojo Blanco
                    }
                    /// USAR POCIONES ///
                    if ((mouse_x >= 184 && mouse_x <= 310) && (mouse_y >= 354 && mouse_y <= 395)) { // Resaltar boton Usar pocion
                        blit(Busarpocion,buffer,0,0,184,354,127,42);
                        textout_ex(buffer,font,"Recuperas 20 puntos de vida",30,460,makecol(255, 255, 255), -1);
                        if (mouse_b & 1) { // Al hacer clic
                            if ((accionar == true) && (pj.pociones > 0)) {
                                if (pj.vida < 100) {
                                    pj.pociones -= 1;
                                    if (pj.vida >= 80) {
                                        pj.vida = 100;
                                        accionar = false;
                                    } else if (pj.vida < 80) {
                                        pj.vida += 20;
                                        accionar = false;
                                    }
                                }
                            }
                        }
                    }

                    masked_blit(mercader,buffer,0,0,100,126,357,201); // Mostrar Mercader

                    textout_ex(buffer,font,"TE HAS TOPADO CON",462,158,makecol(255, 255, 255), -1); // Mostrar mensaje de encuentro
                    textout_ex(buffer,font,"UN MERCADER",462,172,makecol(255, 255, 255), -1);

                    /// AL ELEGIR NO COMPRAR MAS ///
                    if (turno == 0) { // NO HAY ORO SUFICIENTE PARA COMPRAR
                        blit(mercader_precio,buffer,0,0,150,300,62,24); // Mostrar cartel de precio [1]
                        textout_ex(buffer,font,"40",171,306,makecol(0, 0, 0), -1); // Precio

                        blit(mercader_precio,buffer,0,0,247,305,62,24); // Mostrar cartel de precio [2]
                        textout_ex(buffer,font,"40",268,311,makecol(0, 0, 0), -1); // Precio

                        blit(mercader_precio,buffer,0,0,360,300,62,24); // Mostrar cartel de precio [3]
                        textout_ex(buffer,font,"30",381,306,makecol(0, 0, 0), -1); // Precio
                    } else if (pj.oro < 30) { // NO HAY ORO SUFICIENTE PARA COMPRAR
                        blit(mercader_precio,buffer,0,0,150,300,62,24); // Mostrar cartel de precio [1]
                        textout_ex(buffer,font,"40",171,306,makecol(0, 0, 0), -1); // Precio

                        blit(mercader_precio,buffer,0,0,247,305,62,24); // Mostrar cartel de precio [2]
                        textout_ex(buffer,font,"40",268,311,makecol(0, 0, 0), -1); // Precio

                        blit(mercader_precio,buffer,0,0,360,300,62,24); // Mostrar cartel de precio [3]
                        textout_ex(buffer,font,"30",381,306,makecol(0, 0, 0), -1); // Precio

                        textout_ex(buffer, font, "Te has quedado sin", 462, 202, makecol(255, 255, 255), -1);
                        textout_ex(buffer, font, "oro suficiente", 462, 215, makecol(255, 255, 255), -1);

                        if (avanzar == false) {
                            blit(mercader_precio,buffer,0,0,462,262,62,24); // Mostrar opcion: NO
                            textout_ex(buffer,font,"SALIR",464,268,makecol(0, 0, 0), -1);
                            if ((mouse_x >= 462 && mouse_x <= 524) && (mouse_y >= 262 && mouse_y <= 286)) { // Al pasarle el cursor por encima
                                textout_ex(buffer,font,"SALIR",464,268,makecol(255, 0, 0), -1);
                                if (mouse_b & 1) { // Al hacer clic
                                    avanzar = true;
                                }
                            }
                        }
                    } else if ((turno % 2 == 1) && (turno > 0)) { // COMPRAR EN TURNOS IMPARES
                        if (turno == 1) {
                            blit(mercader_precio,buffer,0,0,462,262,62,24); // Mostrar opcion: NO
                            textout_ex(buffer,font,"SALIR",464,268,makecol(0, 0, 0), -1);
                            if ((mouse_x >= 462 && mouse_x <= 524) && (mouse_y >= 262 && mouse_y <= 286)) { // Al pasarle el cursor por encima
                                textout_ex(buffer,font,"SALIR",464,268,makecol(255, 0, 0), -1);
                                if (mouse_b & 1) { // Al hacer clic
                                    avanzar = true;
                                    turno = 0;
                                }
                            }
                        }
                        /// BOTONES DE COMPRA ///
                        blit(mercader_precio,buffer,0,0,150,300,62,24); // Mostrar cartel de precio [1]
                        textout_ex(buffer,font,"40",171,306,makecol(0, 0, 0), -1); // Precio
                        /// COMPRAR [1] ///
                        if ((mouse_x >= 150 && mouse_x <= 212) && (mouse_y >= 300 && mouse_y <= 324)) { // [1] Al pasarle el cursor por encima
                            textout_ex(buffer,font,"40",171,306,makecol(255, 0, 0), -1); // Precio resaltado
                            textout_ex(buffer,font,"+1 de Ataque",30,460,makecol(255, 255, 255), -1); // Mostrar efecto
                            if (mouse_b & 1) { // Al hacer clic
                                if (pj.oro >= 40) {
                                    pj.oro -= 40;
                                    pj.ataque += 1;
                                    turno++;
                                }
                            }
                        }
                        blit(mercader_precio,buffer,0,0,247,305,62,24); // Mostrar cartel de precio [2]
                        textout_ex(buffer,font,"40",268,311,makecol(0, 0, 0), -1); // Precio
                        /// COMPRAR [2] ///
                        if ((mouse_x >= 247 && mouse_x <= 309) && (mouse_y >= 305 && mouse_y <= 329)) { // [2] Al pasarle el cursor por encima
                            textout_ex(buffer,font,"40",268,311,makecol(255, 0, 0), -1); // Precio resaltado
                            textout_ex(buffer,font,"+1 de Defensa",30,460,makecol(255, 255, 255), -1); // Mostrar efecto
                            if (mouse_b & 1) { // Al hacer clic
                                if (pj.oro >= 40) {
                                    pj.oro -= 40;
                                    pj.defensa += 1;
                                    turno++;
                                }
                            }
                        }

                        blit(mercader_precio,buffer,0,0,360,300,62,24); // Mostrar cartel de precio [3]
                        textout_ex(buffer,font,"30",381,306,makecol(0, 0, 0), -1); // Precio
                        /// COMPRAR [3] ///
                        if ((mouse_x >= 360 && mouse_x <= 422) && (mouse_y >= 300 && mouse_y <= 324)) { // [3] Al pasarle el cursor por encima
                            textout_ex(buffer,font,"30",381,306,makecol(255, 0, 0), -1); // Precio resaltado
                            textout_ex(buffer,font,"+20 de vida regenerada",30,460,makecol(255, 255, 255), -1); // Mostrar efecto
                            if (mouse_b & 1) { // Al hacer clic
                                if (pj.oro >= 30) {
                                    pj.oro -= 30;
                                    pj.pociones += 1;
                                    turno++;
                                }
                            }
                        }

                    } else if ((turno % 2 == 0)&& (turno > 0)) { // NO COMPRAR EN TURNOS IMPARES
                        blit(mercader_precio,buffer,0,0,150,300,62,24); // Mostrar cartel de precio [1]
                        textout_ex(buffer,font,"40",171,306,makecol(0, 0, 0), -1); // Precio

                        blit(mercader_precio,buffer,0,0,247,305,62,24); // Mostrar cartel de precio [2]
                        textout_ex(buffer,font,"40",268,311,makecol(0, 0, 0), -1); // Precio

                        blit(mercader_precio,buffer,0,0,360,300,62,24); // Mostrar cartel de precio [3]
                        textout_ex(buffer,font,"30",381,306,makecol(0, 0, 0), -1); // Precio

                        textout_ex(buffer, font, "Seguir comprando:", 462, 202, makecol(255, 255, 255), -1);

                        blit(mercader_precio,buffer,0,0,462,232,62,24); // Mostrar opcion SI
                        textout_ex(buffer,font,"SI",483,238,makecol(0, 0, 0), -1);
                        if ((mouse_x >= 462 && mouse_x <= 524) && (mouse_y >= 232 && mouse_y <= 256)) { // Al pasarle el cursor por encima
                            textout_ex(buffer,font,"SI",483,238,makecol(255, 0, 0), -1);
                            if (mouse_b & 1) { // Al hacer clic
                                avanzar = false;
                                turno++;
                            }
                        }
                        blit(mercader_precio,buffer,0,0,462,262,62,24); // Mostrar opcion: NO
                        textout_ex(buffer,font,"NO",483,268,makecol(0, 0, 0), -1);
                        if ((mouse_x >= 462 && mouse_x <= 524) && (mouse_y >= 262 && mouse_y <= 286)) { // Al pasarle el cursor por encima
                            textout_ex(buffer,font,"NO",483,268,makecol(255, 0, 0), -1);
                            if (mouse_b & 1) { // Al hacer clic
                                avanzar = true;
                                turno = 0;
                            }
                        }
                    }

                    /// BOTON AVANZAR ///
                    if (avanzar == true) {
                        blit(BotonR_verdeB,buffer,0,0,482,424,34,27); // Mostrar Boton R Verde Blanco
                        if ((mouse_x >= 524 && mouse_x <= 623) && (mouse_y >= 424 && mouse_y <= 451)) { // Resaltar boton Avanzar
                            blit(Bavanzar,buffer,0,0,524,424,100,27);
                            textout_ex(buffer, font, "Avanzar a la siguiente zona", 30, 460, makecol(255, 255, 255), -1);
                            if (mouse_b & 1) { // Si se hace click se desactiva el boton Avanzar
                                zona++;
                                avanzar = false;
                                evento = false;
                            }
                        }
                    } else if (avanzar == false) {
                        blit(BotonR_rojoB,buffer,0,0,482,424,34,27); // Mostrar Boton R Rojo Blanco
                    }

                    masked_blit(cursor,buffer,0,0,mouse_x,mouse_y,13,22); // Mostrar cursor
                } while ((evento == true) && (!key[KEY_ESC]));
            }

            /// COFRE MISTERIOSO ///
            if (n_evento > 35 && n_evento <= 40) { // 5% chances de que aparezca una Cofre Misterioso
                int turno(1);
                bool accionar = true; // Controlador de acciones Boton R Azul
                int por_recompensa = 1+rand()%100; // Controlar porcentaje de recompensa
                int recompensa; /* Marcar recompensa para el mensaje
                [1] 20% -> +20-35 oro
                [2] 20% -> +1 pocion curativa
                [3] 30% -> +1 ataque
                [4] 30% -> +1 defensa */
                int oro_recompensa = 20+rand()%16; // Numero aleatorio [20,35] en caso de obtener oro de recompensa

                do {
                    /// ACTIVAR EFECTO UNA SOLA VEZ ///
                    bool efecto;
                    if (turno == 1) {
                        efecto = true;
                    }
                    if (efecto == true) {
                        if (por_recompensa <= 20) { // 20% conseguir 20-35 oro
                            pj.oro += oro_recompensa;
                            recompensa = 1;
                        } else if (por_recompensa > 20 && por_recompensa <= 40) { // 20% conseguir una pocion
                            pj.pociones += 1;
                            recompensa = 2;
                        } else if (por_recompensa > 40 && por_recompensa <= 70) { // 30% conseguir +1 ataque
                            pj.ataque += 1;
                            recompensa = 3;
                        } else if (por_recompensa > 70) { // 30% conseguir +1 defensa
                            pj.defensa += 1;
                            recompensa = 4;
                        }
                        efecto = false;
                        turno++;
                    }

                    // Mostrar pantalla principal
                    blit(buffer,screen,0,0,0,0,640,480);
                    blit(fondo,buffer,0,0,0,0, 640,480); // Fondo principal del juego
                    blit(vida,buffer,0,0,28,28,pj.vida,29); // Barra de Vida
                    blit(mana,buffer,0,0,28,70,pj.mana,29); // Barra de Mana
                    blit(stage1, buffer, 0,0,0,126,453,201); /// Mostrar Stage 1
                    // Mostrar datos pantalla principal
                    textprintf_ex(buffer, font, 100, 32, makecol(0, 0, 0),-1, "%d", pj.vida); // Mostrar Vida
                    textprintf_ex(buffer, font, 100, 74, makecol(0, 0, 0),-1, "%d", pj.mana); // Mostrar Mana
                    textprintf_ex(buffer, font, 310, 42, makecol(0, 0, 0),-1, "%d", pj.ataque); // Mostrar Ataque
                    textprintf_ex(buffer, font, 315, 85, makecol(0, 0, 0),-1, "%d", pj.defensa); // Mostrar Defensa
                    textprintf_ex(buffer, font, 460, 42, makecol(0, 0, 0),-1, "%d", pj.pociones); // Mostrar Pociones
                    textprintf_ex(buffer, font, 425, 85, makecol(230, 236, 16),-1, "%d", pj.oro); // Mostrar Oro
                    textprintf_ex(buffer, font, 590, 366, makecol(0, 0, 0),-1, "%d", zona); // Mostrar Zona

                    /// BOTON R AZUL PARA ACCIONES ///
                    if (accionar == false) {
                        blit(BotonR_rojoB,buffer,0,0,482,368,34,27); // Mostrar Boton R Rojo Blanco
                        if ((mouse_x >= 482 && mouse_x <= 516) && (mouse_y >= 368 && mouse_y <= 395)) { // Resaltar boton Avanzar
                            blit(BotonR_rojoN,buffer,0,0,482,368,34,27);
                            textout_ex(buffer, font, "Habilitar acciones", 30, 460, makecol(255, 255, 255), -1);
                            if (mouse_b & 1) { // Si se hace click se desactiva el boton Avanzar
                                accionar = true;
                            }
                        }
                    } else if (accionar == true) {
                        blit(BotonR_azulB,buffer,0,0,482,368,34,27); // Mostrar Boton R Rojo Blanco
                    }
                    /// USAR POCIONES ///
                    if ((mouse_x >= 184 && mouse_x <= 310) && (mouse_y >= 354 && mouse_y <= 395)) { // Resaltar boton Usar pocion
                        blit(Busarpocion,buffer,0,0,184,354,127,42);
                        textout_ex(buffer,font,"Recuperas 20 puntos de vida",30,460,makecol(255, 255, 255), -1);
                        if (mouse_b & 1) { // Al hacer clic
                            if ((accionar == true) && (pj.pociones > 0)) {
                                if (pj.vida < 100) {
                                    pj.pociones -= 1;
                                    if (pj.vida >= 80) {
                                        pj.vida = 100;
                                        accionar = false;
                                    } else if (pj.vida < 80) {
                                        pj.vida += 20;
                                        accionar = false;
                                    }
                                }
                            }
                        }
                    }

                    masked_blit(cofre_misterioso,buffer,0,0,180,215,157,100); /// Mostrar Cofre Misterioso

                    textout_ex(buffer,font,"HAS ENCONTRADO UN",462,158,makecol(255, 255, 255), -1); // Mostrar mensaje de encuentro
                    textout_ex(buffer,font,"COFRE MISTERIOSO",462,172,makecol(255, 255, 255), -1);

                    /// MENSAJES DE LO OBTENIDO ///
                    if (recompensa == 1) { // ORO
                        textout_ex(buffer,font,"Has encontrado oro",468,202,makecol(255, 255, 255), -1);
                        textprintf_ex(buffer, font, 468, 235, makecol(255, 255, 255),-1, "+ %d", oro_recompensa);
                        textout_ex(buffer,font,"     de oro",468,235,makecol(255, 255, 255), -1);
                    } else if (recompensa == 2) { // POCION
                        textout_ex(buffer,font,"Has encontrado una",468,202,makecol(255, 255, 255), -1);
                        textout_ex(buffer,font,"pocion",468,215,makecol(255, 255, 255), -1);
                        textout_ex(buffer,font,"+ 1 Pocion",468,245,makecol(255, 255, 255), -1);
                    } else if (recompensa == 3) { // ATAQUE
                        textout_ex(buffer,font,"Has encontrado una",468,202,makecol(255, 255, 255), -1);
                        textout_ex(buffer,font,"mejora de ataque",468,215,makecol(255, 255, 255), -1);
                        textout_ex(buffer,font,"+ 1 Ataque",468,245,makecol(255, 255, 255), -1);
                    } else if (recompensa == 4) { // DEFENSA
                        textout_ex(buffer,font,"Has encontrado una",468,202,makecol(255, 255, 255), -1);
                        textout_ex(buffer,font,"mejora de defensa",468,215,makecol(255, 255, 255), -1);
                        textout_ex(buffer,font,"+ 1 Defensa",468,245,makecol(255, 255, 255), -1);
                    }

                    /// BOTON AVANZAR ///
                    if (avanzar == true) {
                        blit(BotonR_verdeB,buffer,0,0,482,424,34,27); /// Mostrar Boton R Verde Blanco
                        if ((mouse_x >= 524 && mouse_x <= 623) && (mouse_y >= 424 && mouse_y <= 451)) { /// Resaltar boton Avanzar
                            blit(Bavanzar,buffer,0,0,524,424,100,27);
                            textout_ex(buffer, font, "Avanzar a la siguiente zona", 30, 460, makecol(255, 255, 255), -1);
                            if (mouse_b & 1) { /// Si se hace click se desactiva el boton Avanzar
                                zona++;
                                avanzar = false;
                                evento = false;
                            }
                        }
                    } else if (avanzar == false) {
                        blit(BotonR_rojoB,buffer,0,0,482,424,34,27); /// Mostrar Boton R Rojo Blanco
                        if ((mouse_x >= 482 && mouse_x <= 517) && (mouse_y >= 424 && mouse_y <= 451)) { /// Resaltar Boton R Rojo Blanco
                            blit(BotonR_rojoN,buffer,0,0,482,424,34,27); /// Mostrar Boton R Rojo Negro
                            textout_ex(buffer, font, "Activar boton Avanzar", 30, 460, makecol(255, 255, 255), -1);
                            if (mouse_b & 1) {
                                avanzar = true;
                            }
                        }
                    }
                    masked_blit(cursor,buffer,0,0,mouse_x,mouse_y,13,22); // Mostrar cursor
                } while ((evento == true) && (!key[KEY_ESC]));
            }

            /// ESQUELETO GUERRERO ///
            if (n_evento > 40) { // 60% chances de que aparezca [1,2] Esqueletos Guerreros
                int turno(1);
                bool accionar = true; // Controlador de acciones Boton R Azul
                int cantidad_enemigos = 1+rand()%2; // Numero aleatorio [1,2] cantidad de enemigos
                int mensaje_enemigos = cantidad_enemigos; // Para mostrar cuantos enemigos aparecieron
                int chance_criticoEnemigo; // Chance de critico enemigo
                int chance_criticoPj; // Chance de critico enemigo
                int danio_enemigo; // Danio causado por el enemigo
                int danio_pj; // Danio causado por el personaje
                bool ataque; // Controlar si el personaje ataca
                bool mensaje_CritEnemigo; // Verificar golpe critico para el mensaje del enemigo
                bool mensaje_CritPj; // Verificar golpe critico para el mensaje del pj
                bool mostrar_mensaje = false; // Controlar si se muestra el mensaje;
                bool detener_mensajes = false; // Detiene mensajes de danio
                int Tcantidad_enemigos = cantidad_enemigos; // Saber cuantos enemigos aparecieron al principio
                int recompensa; // Cuanto oro recibir al derrotarlos
                int Repocion1; // Calcular una pocion
                int Repocion2; // Calcular otra pocion
                int recompensa_pocion = 0; // Cuantas pociones obtienes
                bool obtener_recompensa = true; // Recibir recompensa una sola vez
                bool mostrar_OroObtenido = false; // Activar ultimo mensaje de oro obtenido

                do {
                    // Mostrar pantalla principal
                    blit(buffer,screen,0,0,0,0,640,480);
                    blit(fondo,buffer,0,0,0,0, 640,480); // Fondo principal del juego
                    blit(vida,buffer,0,0,28,28,pj.vida,29); // Barra de Vida
                    blit(mana,buffer,0,0,28,70,pj.mana,29); // Barra de Mana
                    blit(stage1, buffer, 0,0,0,126,453,201); // Mostrar Stage 1
                    // Mostrar datos pantalla principal
                    textprintf_ex(buffer, font, 100, 32, makecol(0, 0, 0),-1, "%d", pj.vida); // Mostrar Vida
                    textprintf_ex(buffer, font, 100, 74, makecol(0, 0, 0),-1, "%d", pj.mana); // Mostrar Mana
                    textprintf_ex(buffer, font, 310, 42, makecol(0, 0, 0),-1, "%d", pj.ataque); // Mostrar Ataque
                    textprintf_ex(buffer, font, 315, 85, makecol(0, 0, 0),-1, "%d", pj.defensa); // Mostrar Defensa
                    textprintf_ex(buffer, font, 460, 42, makecol(0, 0, 0),-1, "%d", pj.pociones); // Mostrar Pociones
                    textprintf_ex(buffer, font, 425, 85, makecol(230, 236, 16),-1, "%d", pj.oro); // Mostrar Oro
                    textprintf_ex(buffer, font, 590, 366, makecol(0, 0, 0),-1, "%d", zona); // Mostrar Zona

                    /// BOTON R AZUL PARA ACCIONES ///
                    if (accionar == false) {
                        blit(BotonR_rojoB,buffer,0,0,482,368,34,27); // Mostrar Boton R Rojo Blanco
                        if ((mouse_x >= 482 && mouse_x <= 516) && (mouse_y >= 368 && mouse_y <= 395)) { // Resaltar boton Avanzar
                            blit(BotonR_rojoN,buffer,0,0,482,368,34,27);
                            textout_ex(buffer, font, "Habilitar acciones", 30, 460, makecol(255, 255, 255), -1);
                            if (mouse_b & 1) { // Si se hace click se desactiva el boton Avanzar
                                accionar = true;
                                mostrar_mensaje = false;
                            }
                        }
                    } else if (accionar == true) {
                        blit(BotonR_azulB,buffer,0,0,482,368,34,27); // Mostrar Boton R Rojo Blanco
                    }
                    /// BOTON USAR POCION ///
                    if (accionar == true) { /// ACTIVAR BOTONES ///
                        if ((mouse_x >= 184 && mouse_x <= 310) && (mouse_y >= 354 && mouse_y <= 395)) { // Resaltar boton Usar pocion
                            blit(Busarpocion,buffer,0,0,184,354,127,42);
                            textout_ex(buffer,font,"Recuperas 20 puntos de vida",30,460,makecol(255, 255, 255), -1);
                            if (mouse_b & 1) { // Al hacer clic
                                if (pj.pociones > 0) {
                                    if (pj.vida < 100) {
                                        pj.pociones -= 1;
                                        if (pj.vida >= 80) {
                                            pj.vida = 100;
                                            accionar = false;
                                            ataque = false;
                                            mostrar_mensaje = true;
                                            detener_mensajes = false;
                                            turno++;
                                        } else if (pj.vida < 80) {
                                            pj.vida += 20;
                                            accionar = false;
                                            ataque = false;
                                            mostrar_mensaje = true;
                                            detener_mensajes = false;
                                            turno++;
                                        }
                                    }
                                }
                            }
                        }
                        /// BOTON ATACAR ///
                        if ((mouse_x >= 28 && mouse_x <= 154) && (mouse_y >= 354 && mouse_y <= 395)) { // Resaltar boton Atacar
                            blit(Batacar,buffer,0,0,28,354,127,42);
                            textout_ex(buffer,font,"Haces dano igual a tu ataque (varia segun la defensa del enemigo)",30,460,makecol(255, 255, 255), -1);
                            if (mouse_b & 1) { // Al hacer clic
                                turno++;
                                accionar = false;
                                ataque = true;
                                mostrar_mensaje = true;
                                detener_mensajes = false;
                            }
                        }
                    }

                    /// ACCIONES DE COMBATE ///
                    if ((turno%2 == 0) && (cantidad_enemigos > 0)) { // Ejecutar cuando se haya elegido una opcion

                        /// Calcular danios con y sin criticos ///
                        esqueleto.danio = 1+rand()%3; // Numero de danio aleatorio [1,3]
                        chance_criticoEnemigo = 1+rand()%100; // Numero aleatorio [1,100]
                        chance_criticoPj = 1+rand()%100; // Numero aleatorio [1,100]
                        if (chance_criticoEnemigo <= 5) { // 5% chances de golpe critico enemigo x2
                            danio_enemigo = (esqueleto.danio * 2) - pj.defensa;
                            if (danio_enemigo <= 0) {
                                danio_enemigo = 1;
                            }
                            mensaje_CritEnemigo = true;
                        } else if (chance_criticoEnemigo > 5) {
                            danio_enemigo = esqueleto.danio - pj.defensa;
                            if (danio_enemigo <= 0) {
                                danio_enemigo = 1;
                            }
                            mensaje_CritEnemigo = false;
                        }
                        if (chance_criticoPj <= 5) { // 5% chances de golpe critico personaje x2
                            danio_pj = (pj.ataque * 2);
                            mensaje_CritPj = true;
                        } else if (chance_criticoPj > 5) {
                            danio_pj = pj.ataque;
                            mensaje_CritPj = false;
                        }

                        /// REALIZAR DANIO ///
                        if (ataque == false) { // SI EL PERSONAJE NO ATACA
                            pj.vida -= danio_enemigo;
                            if (pj.vida <= 0) {
                                pj.vida = 0;
                                break;
                            }
                        } else if (ataque == true) { // SI EL PERSONAJE ATACA
                            esqueleto.vida -= danio_pj;
                            if (esqueleto.vida <= 0) {
                                esqueleto.vida = 0;
                                cantidad_enemigos--;
                                detener_mensajes = true;
                                if (cantidad_enemigos == 0) {
                                    mostrar_OroObtenido = true;
                                }
                            }
                            if (esqueleto.vida > 0) {
                                pj.vida -= danio_enemigo;
                                if (pj.vida <= 0) {
                                    pj.vida = 0;
                                    break;
                                }
                            }
                        }
                        if (esqueleto.vida == 0) {
                            esqueleto.vida = 10;
                        }
                        turno++;
                    }

                    /// MENSAJES DE ACCIONES SI EL PERSONAJE NO ATACO ///
                    if ((mostrar_mensaje == true) && (ataque == false) && (cantidad_enemigos > 0)) {
                        if (mensaje_CritEnemigo == true) { // Mensaje critico
                            textout_ex(buffer,font,"[ GOLPE CRITICO ]",468,202,makecol(255, 255, 255), -1);
                            textprintf_ex(buffer, font, 468, 215, makecol(255, 255, 255),-1, "Pierdes %d", danio_enemigo);
                            textout_ex(buffer,font,"          de vida",468,215,makecol(255, 255, 255), -1);
                        } else if (mensaje_CritEnemigo == false) {
                            textprintf_ex(buffer, font, 468, 215, makecol(255, 255, 255),-1, "Pierdes %d", danio_enemigo);
                            textout_ex(buffer,font,"          de vida",468,215,makecol(255, 255, 255), -1);
                        }
                    }
                    /// MENSAJES DE ACCIONES SI EL PERSONAJE ATACA ///
                    else if ((mostrar_mensaje == true) && (ataque == true) && (cantidad_enemigos > 0) && (detener_mensajes == false)) {
                        if (mensaje_CritEnemigo == true) { // Mensaje critico
                            textout_ex(buffer,font,"[ GOLPE CRITICO ]",468,202,makecol(255, 255, 255), -1);
                            textprintf_ex(buffer, font, 468, 215, makecol(255, 255, 255),-1, "Pierdes %d", danio_enemigo);
                            textout_ex(buffer,font,"          de vida",468,215,makecol(255, 255, 255), -1);
                        } else if (mensaje_CritEnemigo == false) {
                            textprintf_ex(buffer, font, 468, 215, makecol(255, 255, 255),-1, "Pierdes %d", danio_enemigo);
                            textout_ex(buffer,font,"          de vida",468,215,makecol(255, 255, 255), -1);
                        }
                        if (mensaje_CritPj == true) { // Mensaje critico
                            textout_ex(buffer,font,"[ GOLPE CRITICO ]",468,252,makecol(255, 255, 255), -1);
                            textprintf_ex(buffer, font, 468, 265, makecol(255, 255, 255),-1, "Haces %d", danio_pj);
                            textout_ex(buffer,font,"        de dano",468,265,makecol(255, 255, 255), -1);
                        } else if (mensaje_CritPj == false) {
                            textprintf_ex(buffer, font, 468, 265, makecol(255, 255, 255),-1, "Haces %d", danio_pj);
                            textout_ex(buffer,font,"        de dano",468,265,makecol(255, 255, 255), -1);
                        }
                    }

                    /// MOSTRAR ENEMIGOS ///
                    if (cantidad_enemigos == 1) {
                        masked_blit(esqueleto_guerrero,buffer,0,0,85,210,132,96);
                        // Mostrar barra de vida del enemigo marcado
                        if (turno == 1) {
                            esqueleto.vida = 10; // Reiniciar vida del enemigo
                        }
                        esqueleto.barra_vida = ((esqueleto.vida * 128)/10); // (vida_actual * pixel_maximo) / vida_maxima
                        blit(marco_vidaEsqueleto,buffer,0,0,85,309,132,22); // Marco de la vida
                        blit(vida_enemigo,buffer,0,0,87,311,esqueleto.barra_vida,18); // Barra de vida
                        textprintf_ex(buffer, font, 195, 314, makecol(0, 0, 0),-1, "%d", esqueleto.vida); // Mostrar numero vida
                    } else if (cantidad_enemigos == 2) {
                        masked_blit(esqueleto_guerrero,buffer,0,0,85,210,132,96);
                        masked_blit(esqueleto_guerreroMarcado,buffer,0,0,245,140,132,146);
                        // Mostrar barra de vida del enemigo marcado
                        if (turno == 1) {
                            esqueleto.vida = 10; // Reiniciar vida del enemigo
                        }
                        esqueleto.barra_vida = ((esqueleto.vida * 128)/10); // (vida_actual * pixel_maximo) / vida_maxima
                        blit(marco_vidaEsqueleto,buffer,0,0,245,291,132,22); // Marco de la vida
                        blit(vida_enemigo,buffer,0,0,247,293,esqueleto.barra_vida,18); // Barra de vida
                        textprintf_ex(buffer, font, 355, 296, makecol(0, 0, 0),-1, "%d", esqueleto.vida); // Mostrar numero vida
                    }

                    /// MOSTRAR MENSAJE CANTIDAD DE ENEMIGOS QUE APARECIERON ///
                    if (cantidad_enemigos > 0) {
                        textout_ex(buffer,font,"HAS SIDO EMBOSCADO POR",460,158,makecol(255, 255, 255), -1); // Mostrar mensaje de encuentro
                        if (mensaje_enemigos == 1) {
                            textout_ex(buffer,font,"UN ESQUELETO GUERRERO",460,172,makecol(255, 255, 255), -1);
                        } else if (mensaje_enemigos == 2) {
                            textout_ex(buffer,font,"2 ESQUELETOS GUERREROS",460,172,makecol(255, 255, 255), -1);
                        }
                    } else if ((cantidad_enemigos == 0)) {
                        textout_ex(buffer,font,"ENEMIGOS DERROTADOS",460,158,makecol(255, 255, 255), -1); // Mostrar mensaje de encuentro
                        /// ENTREGAR RECOMPENSA EN ORO ///
                        if (mostrar_OroObtenido == true) {
                            if (Tcantidad_enemigos == 1) {
                                Repocion1 = 1+rand()%100; // Numero aleatorio [1,100]
                                if (Repocion1 <= 5) {
                                    recompensa_pocion++;
                                }
                                recompensa = 5+rand()%3; // Numero aleatorio entre [5,7]
                            } else if (Tcantidad_enemigos == 2) {
                                Repocion1 = 1+rand()%100; // Numero aleatorio [1,100]
                                Repocion2 = 1+rand()%100; // Numero aleatorio [1,100]
                                if (Repocion1 <= 5) {
                                    recompensa_pocion++;
                                }
                                if (Repocion2 <= 5) {
                                    recompensa_pocion++;
                                }
                                recompensa = 10+rand()%5; // Numero aleatorio entre [10,14]
                            }
                            mostrar_OroObtenido = false;
                        }
                        textprintf_ex(buffer, font, 468, 215, makecol(255, 255, 255),-1, "Obtienes %d", recompensa);
                        textout_ex(buffer,font,"            de oro",468,215,makecol(255, 255, 255), -1);
                        if (recompensa_pocion > 0) {
                            textprintf_ex(buffer, font, 468, 234, makecol(255, 255, 255),-1, "Obtienes %d", recompensa_pocion);
                            if (recompensa_pocion == 1) {
                                textout_ex(buffer,font,"            pocions",468,234,makecol(255, 255, 255), -1);
                            } else if (recompensa_pocion == 2) {
                                textout_ex(buffer,font,"            pociones",468,234,makecol(255, 255, 255), -1);
                            }
                        }
                        if (obtener_recompensa == true) {
                            pj.oro += recompensa;
                            obtener_recompensa = false;
                        }
                    }

                    /// BOTON AVANZAR ///
                    if (cantidad_enemigos == 0) { // Habilitar boton Avanzar al acabar con todos los enemigos
                        avanzar = true;
                    }
                    if (avanzar == true) {
                        blit(BotonR_verdeB,buffer,0,0,482,424,34,27); // Mostrar Boton R Verde Blanco
                        if ((mouse_x >= 524 && mouse_x <= 623) && (mouse_y >= 424 && mouse_y <= 451)) { // Resaltar boton Avanzar
                            blit(Bavanzar,buffer,0,0,524,424,100,27);
                            textout_ex(buffer, font, "Avanzar a la siguiente zona", 30, 460, makecol(255, 255, 255), -1);
                            if (mouse_b & 1) { // Si se hace click se desactiva el boton Avanzar
                                zona++;
                                avanzar = false;
                                evento = false;
                            }
                        }
                    } else if (avanzar == false) {
                        blit(BotonR_rojoB,buffer,0,0,482,424,34,27); // Mostrar Boton R Rojo Blanco
                    }
                    masked_blit(cursor,buffer,0,0,mouse_x,mouse_y,13,22); // Mostrar cursor
                } while ((evento == true) && (!key[KEY_ESC]) && (pj.vida > 0));
            }

            /// SI SE MUERE ///
            if (pj.vida <= 0) {
                break;
            }
        }
////////// FIN ZONA 1-19 - Stage 1///

        masked_blit(cursor,buffer,0,0,mouse_x,mouse_y,13,22); // Mostrar cursor
    }

    destroy_bitmap(buffer);
    return 0;
}
END_OF_MAIN()
