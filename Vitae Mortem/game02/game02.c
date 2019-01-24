#include "game02.h"
#include "imagen.h"
#include "graphics.h"
#include "ebentoak.h"
#include "text.h"
#include "soinua.h"
#include <stdio.h>
#include <windows.h>

#define ONGI_ETORRI_MEZUA "Sakatu return hasteko..."
#define JOKOA_SOUND ".\\sound\\132TRANCE_02.wav"
#define JOKOA_PLAYER_IMAGE ".\\img\\invader.bmp"
#define JOKOA_SOUND_WIN ".\\sound\\BugleCall.wav"
#define JOKOA_SOUND_LOOSE ".\\sound\\terminator.wav" 
#define BUKAERA_SOUND_1 ".\\sound\\128NIGHT_01.wav"
#define BUKAERA_IMAGE ".\\img\\gameOver_1.bmp"

int JOKOA_jokalariaIrudiaSortu();
//void zirkuluaBistaratu(int xRef, int yRef);
void JOKOA_lerroHBatMargotu(int x, int y, int x1, int y1);
void JOKOA_lerroVBatMargotu(int x, int y, int x1, int y1);
EGOERA JOKOA_egoera(JOKO_ELEMENTUA jokalaria, JOKO_ELEMENTUA oztopoa);
POSIZIOA ERREALITATE_FISIKOA_mugimendua(POSIZIOA posizioa);
//int  BUKAERA_menua(EGOERA egoera);
int BUKAERA_irudiaBistaratu();
void jokoaAurkeztu();
EGOERA jokatu();

void jokoaAurkeztu(void)
{
	int ebentu = 0, irten = 0, soinua = 0, mugitu = 0;
	POSIZIOA pos;
	JOKO_ELEMENTUA hasiera, Kredituak, Ezarpenak;

	audioInit();
	loadTheMusic(JOKOA_SOUND);
	playMusic();

	while (!irten) {
		hasiera.id = JOKOA_jokalariaIrudiaPortada();

		while (!irten)
		{
			ebentu = ebentuaJasoGertatuBada();
			if (ebentu == SAGU_BOTOIA_EZKERRA)
			{
				pos = saguarenPosizioa();
				if ((pos.x > 69) && (pos.x < 69 + 135) && (pos.y > 268) && (pos.y < 268 + 28))
				{
					irudiaKendu(hasiera.id);
					pantailaGarbitu();
					pantailaBerriztu();
					irten = 1;
				}
				else if ((pos.x > 55) && (pos.x < 55 + 145) && (pos.y > 326) && (pos.y < 326 + 28)) irten = 2;
				else if ((pos.x > 55) && (pos.x < 55 + 145) && (pos.y > 406) && (pos.y < 406 + 28)) irten = 3;
			}
		}
		if (irten == 2)
		{
			Ezarpenak.id = JOKOA_jokalariaIrudiaEzarpenak();

		}
		while (irten == 2)
		{
			ebentu = ebentuaJasoGertatuBada();
			if (ebentu == SAGU_BOTOIA_EZKERRA)
			{
				pos = saguarenPosizioa();
				if ((pos.x > 522) && (pos.x < 522 + 96) && (pos.y > 37) && (pos.y < 37 + 16))
				{
					irudiaKendu(Ezarpenak.id);
					pantailaGarbitu();
					pantailaBerriztu();
					irten = 0;
				}
				else if ((pos.x > 555) && (pos.x < 555 + 50) && (pos.y > 223) && (pos.y < 223 + 50)) {
					toggleMusic();
				}
			}


		}


		if (irten == 3)
		{
			Kredituak.id = JOKOA_jokalariaIrudiaKredituak();
		}
		while (irten == 3)
		{
			ebentu = ebentuaJasoGertatuBada();
			if (ebentu == SAGU_BOTOIA_EZKERRA)
			{
				pos = saguarenPosizioa();
				if ((pos.x > 522) && (pos.x < 522 + 96) && (pos.y > 37) && (pos.y < 37 + 16)) {
					irudiaKendu(Kredituak.id);
					pantailaGarbitu();
					pantailaBerriztu();
					irten = 0;
				}

			}
		}
	}

	irudiaKendu(hasiera.id);

}

EGOERA jokatu(void)
{
	int mugitu = 0; //boolean
	EGOERA  egoera = JOLASTEN;
	int ebentu = 0;
	JOKO_ELEMENTUA  jokalaria, obstakulua, fondo, fondo2,  meta, tutorial;


	//Uint32 time01 = SDL_GetTicks(), time02;

	//JOKOKO ELEMENTUEN POSIZIOAK
	jokalaria.pos.x = 0;
	jokalaria.pos.y = 425;


	obstakulua.pos.x = 300;
	obstakulua.pos.y = 435;

	fondo2.pos.x = 0;
	fondo2.pos.y = 20;

	fondo.pos.x = 0;
	fondo.pos.y = 50;

	tutorial.pos.x = 0;
	tutorial.pos.y = 0;

	meta.pos.x = 450;
	meta.pos.y = 410;

	//IRUDIAK KARGATU
	fondo.id = JOKOA_jokalariaIrudiaFondo();
	fondo2.id = JOKOA_jokalariaIrudiaFondo();
	meta.id = JOKOA_jokalariaIrudiaMeta();
	tutorial.id = JOKOA_jokalariaIrudiaTutorial();
	jokalaria.id = JOKOA_jokalariaIrudiaPersaonajea();
	obstakulua.id = JOKOA_jokalariaIrudiaPintxoak();

	//IRUDIEI POSIZIOA JARRI
	irudiaMugitu(fondo.id, fondo.pos.x, fondo.pos.y);
	irudiaMugitu(fondo2.id, fondo2.pos.x, fondo2.pos.y);
	irudiaMugitu(obstakulua.id, obstakulua.pos.x, obstakulua.pos.y);
	irudiaMugitu(meta.id, meta.pos.x, meta.pos.y);
	irudiakMarraztu();
	int i = 0, x = 0, k = 0;
	do {
		Sleep(12);
		pantailaGarbitu();
		irudiaMugitu(jokalaria.id, jokalaria.pos.x, jokalaria.pos.y);
		irudiaMugitu(tutorial.id, tutorial.pos.x, tutorial.pos.y);
		irudiakMarraztu();
		pantailaBerriztu();

		//PERTSONAIAREN MUGIMENDUA
		ebentu = ebentuaJasoGertatuBada();
		if (ebentu == TECLA_RIGHT || ebentu == TECLA_LEFT)
		{
			if (ebentu == TECLA_RIGHT)
			{
				jokalaria.pos.x = jokalaria.pos.x + 12;
			}
			else
			{
				jokalaria.pos.x = jokalaria.pos.x - 12;
			}
		}

		if ((ebentu == TECLA_SPACE) && (i == 0))i = 1;
		if ((i > 0) && (i < 10))
		{
			jokalaria.pos.y = jokalaria.pos.y - 12;
			i++;
		}
		if ((i >= 10) && (i < 100))
		{
			jokalaria.pos.y++;
			i++;
		}
		if (i == 100)i = 0;
		jokalaria.pos.y = jokalaria.pos.y + 1;
		if (jokalaria.pos.y > 423)jokalaria.pos.y = 423;

		//PERTSONAIA ETA OBSTAKULUEN ARTEKO KOLISIOAK
		egoera = JOKOA_egoera(jokalaria, obstakulua);
		
		if (jokalaria.pos.x > meta.pos.x - 20 && jokalaria.pos.x <meta.pos.x + 20 && jokalaria.pos.y >meta.pos.y - 20 && jokalaria.pos.y < meta.pos.y + 20)
		{
			irudiaKendu(jokalaria.id);
			irudiaKendu(obstakulua.id);
			irudiaKendu(meta.id);
			irudiaKendu(fondo2.id);
			jokatu1();
		}
	} while (egoera == JOLASTEN);
	irudiaKendu(jokalaria.id);
	irudiaKendu(obstakulua.id);
	irudiaKendu(meta.id);
	irudiaKendu(fondo2.id);
	irudiaKendu(tutorial.id);
	jokatu();
	return egoera;
}

EGOERA jokatu1(void)
{
	int mugitu = 0; //boolean
	EGOERA  egoera = JOLASTEN, egoera1 = JOLASTEN, egoera2 = JOLASTEN, egoera3 = JOLASTEN, egoera4 = JOLASTEN, egoera5 = JOLASTEN, egoera6 = JOLASTEN;
	int ebentu = 0;
	JOKO_ELEMENTUA  jokalaria, obstakulua, obstakulua4, obstakulua5, obstakulua6, obstakulua7, obstakulua8, fondo, meta;

	//Uint32 time01 = SDL_GetTicks(), time02;


	//JOKOKO ELEMENTUEN POSIZIOAK
	jokalaria.pos.x = 0;
	jokalaria.pos.y = 425;

	obstakulua.pos.x = 200;
	obstakulua.pos.y = 435;

	obstakulua4.pos.x = 435;
	obstakulua4.pos.y = 435;

	obstakulua5.pos.x = 470;
	obstakulua5.pos.y = 435;


	obstakulua6.pos.x = 505;
	obstakulua6.pos.y = 435;

	obstakulua7.pos.x = 540;
	obstakulua7.pos.y = 435;

	obstakulua8.pos.x = 575;
	obstakulua8.pos.y = 435;

	fondo.pos.x = 0;
	fondo.pos.y = 20;

	meta.pos.x = 590;
	meta.pos.y = 225;

	//IRUDIAK KARGATU
	fondo.id = JOKOA_jokalariaIrudiaFondo();
	meta.id = JOKOA_jokalariaIrudiaMeta();
	jokalaria.id = JOKOA_jokalariaIrudiaPersaonajea();
	obstakulua.id = JOKOA_jokalariaIrudiaPintxoak();
	obstakulua4.id = JOKOA_jokalariaIrudiaPintxoak();
	obstakulua5.id = JOKOA_jokalariaIrudiaPintxoak();
	obstakulua6.id = JOKOA_jokalariaIrudiaPintxoak();
	obstakulua7.id = JOKOA_jokalariaIrudiaPintxoak();
	obstakulua8.id = JOKOA_jokalariaIrudiaPintxoak();

	//IRUDIEI POSIZIOA JARRI
	irudiaMugitu(fondo.id, fondo.pos.x, fondo.pos.y);
	irudiaMugitu(obstakulua.id, obstakulua.pos.x, obstakulua.pos.y);
	irudiaMugitu(obstakulua4.id, obstakulua4.pos.x, obstakulua4.pos.y);
	irudiaMugitu(obstakulua5.id, obstakulua5.pos.x, obstakulua5.pos.y);
	irudiaMugitu(obstakulua6.id, obstakulua6.pos.x, obstakulua6.pos.y);
	irudiaMugitu(obstakulua7.id, obstakulua7.pos.x, obstakulua7.pos.y);
	irudiaMugitu(obstakulua8.id, obstakulua8.pos.x, obstakulua8.pos.y);

	irudiaMugitu(meta.id, meta.pos.x, meta.pos.y);
	irudiakMarraztu();
	int i = 0, x = 0;
	do {
		Sleep(4);
		pantailaGarbitu();
		irudiaMugitu(jokalaria.id, jokalaria.pos.x, jokalaria.pos.y);
		irudiakMarraztu();

		//KARRATUAK SORTU ETA KOLISIOAK
		karratuaMarraztu(240, 400, 275, 455);
		jokalaria.pos.x = kolisioakDetektatuX(240, 400, 275, 455, jokalaria.pos.x, jokalaria.pos.y);
		jokalaria.pos.y = kolisioakDetektatuY(240, 400, 275, 455, jokalaria.pos.x, jokalaria.pos.y);
		arkatzKoloreaEzarri(255, 255, 255);
		karratuaMarraztu(315, 350, 370, 455);
		jokalaria.pos.x = kolisioakDetektatuX(315, 350, 370, 455, jokalaria.pos.x, jokalaria.pos.y);
		jokalaria.pos.y = kolisioakDetektatuY(315, 350, 370, 455, jokalaria.pos.x, jokalaria.pos.y);
		arkatzKoloreaEzarri(255, 255, 255);
		karratuaMarraztu(410, 290, 440, 320);
		jokalaria.pos.x = kolisioakDetektatuX(410, 290, 440, 320, jokalaria.pos.x, jokalaria.pos.y);
		jokalaria.pos.y = kolisioakDetektatuY(410, 290, 440, 320, jokalaria.pos.x, jokalaria.pos.y);
		arkatzKoloreaEzarri(255, 255, 255);
		karratuaMarraztu(510, 270, 650, 310);
		jokalaria.pos.x = kolisioakDetektatuX(510, 270, 650, 310, jokalaria.pos.x, jokalaria.pos.y);
		jokalaria.pos.y = kolisioakDetektatuY(510, 270, 650, 310, jokalaria.pos.x, jokalaria.pos.y);
		arkatzKoloreaEzarri(255, 255, 255);
		pantailaBerriztu();

		//PERTSONAIAREN MUGIMENDUA
		ebentu = ebentuaJasoGertatuBada();
		if (ebentu == TECLA_RIGHT || ebentu == TECLA_LEFT)
		{
			if (ebentu == TECLA_RIGHT)
			{
				jokalaria.pos.x = jokalaria.pos.x + 12;
			}
			else
			{
				jokalaria.pos.x = jokalaria.pos.x - 12;
			}
		}

		if ((ebentu == TECLA_SPACE) && (i == 0))i = 1;
		if ((i > 0) && (i < 10))
		{
			jokalaria.pos.y = jokalaria.pos.y - 12;
			i++;
		}
		if ((i >= 10) && (i < 50))
		{
			jokalaria.pos.y++;
			i++;
		}
		if (i == 50)i = 0;
		jokalaria.pos.y = jokalaria.pos.y + 1;
		if (jokalaria.pos.y > 423)jokalaria.pos.y = 423;

		//PERTSONAIA ETA OBSTAKULUEN ARTEKO KOLISIOAK
		egoera = JOKOA_egoera(jokalaria, obstakulua);
		egoera2 = JOKOA_egoera(jokalaria, obstakulua4);
		egoera3 = JOKOA_egoera(jokalaria, obstakulua5);
		egoera4 = JOKOA_egoera(jokalaria, obstakulua6);
		egoera5 = JOKOA_egoera(jokalaria, obstakulua7);
		egoera6 = JOKOA_egoera(jokalaria, obstakulua8);
		if (jokalaria.pos.x > meta.pos.x - 20 && jokalaria.pos.x <meta.pos.x + 20 && jokalaria.pos.y >meta.pos.y - 20 && jokalaria.pos.y < meta.pos.y + 20)
		{
			irudiaKendu(jokalaria.id);
			irudiaKendu(obstakulua.id);
			irudiaKendu(obstakulua4.id);
			irudiaKendu(obstakulua5.id);
			irudiaKendu(obstakulua6.id);
			irudiaKendu(obstakulua7.id);
			irudiaKendu(obstakulua8.id);
			irudiaKendu(meta.id);
			irudiaKendu(fondo.id);
			jokatu2();
		}
	} while ((egoera == JOLASTEN) && (egoera2 == JOLASTEN) && (egoera3 == JOLASTEN) && (egoera4 == JOLASTEN) && (egoera5 == JOLASTEN) && (egoera6 == JOLASTEN));
	irudiaKendu(jokalaria.id);
	irudiaKendu(obstakulua.id);
	irudiaKendu(obstakulua4.id);
	irudiaKendu(obstakulua5.id);
	irudiaKendu(obstakulua6.id);
	irudiaKendu(obstakulua7.id);
	irudiaKendu(obstakulua8.id);
	irudiaKendu(meta.id);
	irudiaKendu(fondo.id);
	jokatu1();
	return egoera;
}

EGOERA jokatu2(void)
{
	int mugitu = 0; //boolean
	EGOERA  egoera = JOLASTEN, egoera1 = JOLASTEN, egoera2 = JOLASTEN, egoera3 = JOLASTEN, egoera4 = JOLASTEN, egoera5 = JOLASTEN, egoera6 = JOLASTEN;
	int ebentu = 0;
	JOKO_ELEMENTUA  jokalaria, zerra, obstakulua, obstakulua4, obstakulua5, obstakulua6, obstakulua7, obstakulua8, fondo, meta;

	//Uint32 time01 = SDL_GetTicks(), time02;

	//JOKOKO ELEMENTUEN POSIZIOAK
	jokalaria.pos.x = 0;
	jokalaria.pos.y = 425;

	zerra.pos.x = 200;
	zerra.pos.y = 310;

	obstakulua.pos.x = 150;
	obstakulua.pos.y = 350;

	obstakulua4.pos.x = 405;
	obstakulua4.pos.y = 350;

	obstakulua5.pos.x = 330;
	obstakulua5.pos.y = 250;


	obstakulua6.pos.x = 500;
	obstakulua6.pos.y = 435;

	obstakulua7.pos.x = 545;
	obstakulua7.pos.y = 435;

	obstakulua8.pos.x = 590;
	obstakulua8.pos.y = 435;

	fondo.pos.x = 0;
	fondo.pos.y = 20;

	meta.pos.x = 180;
	meta.pos.y = 155;

	//IRUDIAK KARGATU
	fondo.id = JOKOA_jokalariaIrudiaFondo();
	meta.id = JOKOA_jokalariaIrudiaMeta();
	jokalaria.id = JOKOA_jokalariaIrudiaPersaonajea();
	obstakulua.id = JOKOA_jokalariaIrudiaPintxoak();
	obstakulua4.id = JOKOA_jokalariaIrudiaPintxoak();
	obstakulua5.id = JOKOA_jokalariaIrudiaPintxoak();
	obstakulua6.id = JOKOA_jokalariaIrudiaPintxoak();
	obstakulua7.id = JOKOA_jokalariaIrudiaPintxoak();
	obstakulua8.id = JOKOA_jokalariaIrudiaPintxoak();
	zerra.id = JOKOA_jokalariaIrudiaZerra();
	
	//IRUDIEI POSIZIOA JARRI
	irudiaMugitu(fondo.id, fondo.pos.x, fondo.pos.y);
	irudiaMugitu(obstakulua.id, obstakulua.pos.x, obstakulua.pos.y);
	irudiaMugitu(obstakulua4.id, obstakulua4.pos.x, obstakulua4.pos.y);
	irudiaMugitu(obstakulua5.id, obstakulua5.pos.x, obstakulua5.pos.y);
	irudiaMugitu(obstakulua6.id, obstakulua6.pos.x, obstakulua6.pos.y);
	irudiaMugitu(obstakulua7.id, obstakulua7.pos.x, obstakulua7.pos.y);
	irudiaMugitu(obstakulua8.id, obstakulua8.pos.x, obstakulua8.pos.y);

	irudiaMugitu(meta.id, meta.pos.x, meta.pos.y);
	irudiakMarraztu();
	int i = 0, x=0, k=0;
	do {
		Sleep(2);
		pantailaGarbitu();
		irudiaMugitu(zerra.id, zerra.pos.x, zerra.pos.y);
		zerra.pos.x=serraBertikal(zerra.pos.x, k);
		k = k + 2;
		if (k == 250)k = 0;
		irudiaMugitu(jokalaria.id, jokalaria.pos.x, jokalaria.pos.y);
		irudiakMarraztu();

		//KARRATUAK SORTU ETA KOLISIOAK
		karratuaMarraztu(90, 410, 120, 455);
		jokalaria.pos.x=kolisioakDetektatuX(90, 410, 120, 455, jokalaria.pos.x, jokalaria.pos.y);
		jokalaria.pos.y = kolisioakDetektatuY(90, 410, 120, 455, jokalaria.pos.x, jokalaria.pos.y);
		arkatzKoloreaEzarri(255, 255, 255);
		karratuaMarraztu(120, 370, 260, 455);
		jokalaria.pos.x = kolisioakDetektatuX(120, 370, 260, 455, jokalaria.pos.x, jokalaria.pos.y);
		jokalaria.pos.y = kolisioakDetektatuY(120, 370, 260, 455, jokalaria.pos.x, jokalaria.pos.y);
		arkatzKoloreaEzarri(255, 255, 255);
		karratuaMarraztu(260, 420, 320, 455);
		jokalaria.pos.x = kolisioakDetektatuX(260, 420, 320, 455, jokalaria.pos.x, jokalaria.pos.y);
		jokalaria.pos.y = kolisioakDetektatuY(260, 420, 320, 455, jokalaria.pos.x, jokalaria.pos.y);
		arkatzKoloreaEzarri(255, 255, 255);
		karratuaMarraztu(320, 370, 490, 455);
		jokalaria.pos.x = kolisioakDetektatuX(320, 370, 490, 455, jokalaria.pos.x, jokalaria.pos.y);
		jokalaria.pos.y = kolisioakDetektatuY(320, 370, 490, 455, jokalaria.pos.x, jokalaria.pos.y);
		arkatzKoloreaEzarri(255, 255, 255);
		karratuaMarraztu(470, 300, 490, 370);
		jokalaria.pos.x = kolisioakDetektatuX(470, 300, 490, 370, jokalaria.pos.x, jokalaria.pos.y);
		jokalaria.pos.y = kolisioakDetektatuY(470, 300, 490, 370, jokalaria.pos.x, jokalaria.pos.y);
		arkatzKoloreaEzarri(255, 255, 255);
		karratuaMarraztu(200, 270, 400, 290);
		jokalaria.pos.x = kolisioakDetektatuX(200, 270, 400, 290, jokalaria.pos.x, jokalaria.pos.y);
		jokalaria.pos.y = kolisioakDetektatuY(200, 270, 400, 290, jokalaria.pos.x, jokalaria.pos.y);
		arkatzKoloreaEzarri(255, 255, 255);
		karratuaMarraztu(200, 200, 220, 270);
		jokalaria.pos.x = kolisioakDetektatuX(200, 200, 220, 270, jokalaria.pos.x, jokalaria.pos.y);
		jokalaria.pos.y = kolisioakDetektatuY(200, 200, 220, 270, jokalaria.pos.x, jokalaria.pos.y);
		arkatzKoloreaEzarri(255, 255, 255);
		pantailaBerriztu();

		//PERTSONAIAREN MUGIMENDUA
		ebentu = ebentuaJasoGertatuBada();
		if (ebentu == TECLA_RIGHT || ebentu == TECLA_LEFT)
		{
			if (ebentu == TECLA_RIGHT)
			{
				jokalaria.pos.x = jokalaria.pos.x + 12;
			}
			else
			{
				jokalaria.pos.x = jokalaria.pos.x - 15;
			}
		}

		if ((ebentu == TECLA_SPACE)&&(i==0))i=1;
		if ((i > 0)&&(i<10))
		{
			jokalaria.pos.y = jokalaria.pos.y - 13;
			i++;
		}
		if ((i >= 10) && (i < 50))
		{
			jokalaria.pos.y++;
			i++;
		}
		if (i == 50)i = 0;
		jokalaria.pos.y=jokalaria.pos.y+2;
		if (jokalaria.pos.y > 423)jokalaria.pos.y = 423;

		//PERTSONAIA ETA OBSTAKULUEN ARTEKO KOLISIOAK
		egoera = JOKOA_egoera(jokalaria, obstakulua);
		egoera1 = JOKOA_egoeraZerra(jokalaria, zerra);
		egoera2 = JOKOA_egoera(jokalaria, obstakulua4);
		egoera3 = JOKOA_egoera(jokalaria, obstakulua5);
		egoera4 = JOKOA_egoera(jokalaria, obstakulua6);
		egoera5= JOKOA_egoera(jokalaria, obstakulua7);
		egoera6 = JOKOA_egoera(jokalaria, obstakulua8);

		if (jokalaria.pos.x > meta.pos.x - 20 && jokalaria.pos.x <meta.pos.x + 20 && jokalaria.pos.y >meta.pos.y - 20 && jokalaria.pos.y < meta.pos.y + 20)
		{
			irudiaKendu(jokalaria.id);
			irudiaKendu(obstakulua.id);
			irudiaKendu(obstakulua4.id);
			irudiaKendu(obstakulua5.id);
			irudiaKendu(obstakulua6.id);
			irudiaKendu(obstakulua7.id);
			irudiaKendu(obstakulua8.id);
			irudiaKendu(zerra.id);
			irudiaKendu(meta.id);
			irudiaKendu(fondo.id);
			jokatu3();
		}
	} while ((egoera == JOLASTEN) && (egoera1 == JOLASTEN)&& (egoera2 == JOLASTEN) && (egoera3 == JOLASTEN) && (egoera4 == JOLASTEN) && (egoera5 == JOLASTEN) && (egoera6 == JOLASTEN));
	irudiaKendu(jokalaria.id);
	irudiaKendu(obstakulua.id);
	irudiaKendu(obstakulua4.id);
	irudiaKendu(obstakulua5.id);
	irudiaKendu(obstakulua6.id);
	irudiaKendu(obstakulua7.id);
	irudiaKendu(obstakulua8.id);
	irudiaKendu(zerra.id);
	irudiaKendu(meta.id);
	irudiaKendu(fondo.id);
	jokatu2();

	return egoera;
}

EGOERA jokatu3(void)
{
	int mugitu = 0; //boolean
	EGOERA  egoera = JOLASTEN, egoera1 = JOLASTEN, egoera2 = JOLASTEN, egoera3 = JOLASTEN, egoera4 = JOLASTEN, egoera5 = JOLASTEN, egoera6 = JOLASTEN, egoera7 = JOLASTEN;
	int ebentu = 0;
	JOKO_ELEMENTUA  jokalaria, kainon, fuego, obstakulua, obstakulua4, obstakulua5, obstakulua6, obstakulua7, obstakulua8, fondo, meta;

	//Uint32 time01 = SDL_GetTicks(), time02;

	//JOKOKO ELEMENTUEN POSIZIOAK
	jokalaria.pos.x = 0;
	jokalaria.pos.y = 425;

	obstakulua.pos.x = 180;
	obstakulua.pos.y = 380;

	obstakulua4.pos.x = 345;
	obstakulua4.pos.y = 380;

	obstakulua5.pos.x = 260;
	obstakulua5.pos.y = 270;


	obstakulua6.pos.x = 520;
	obstakulua6.pos.y = 435;

	obstakulua7.pos.x = 440;
	obstakulua7.pos.y = 130;

	obstakulua8.pos.x = 570;
	obstakulua8.pos.y = 435;

	fondo.pos.x = 0;
	fondo.pos.y = 20;

	fuego.pos.x = 510;
	fuego.pos.y = 110;

	meta.pos.x = 535;
	meta.pos.y = 410;

	kainon.pos.x = 470;
	kainon.pos.y = 0;

	//IRUDIAK KARGATU
	fondo.id = JOKOA_jokalariaIrudiaFondo();
	meta.id = JOKOA_jokalariaIrudiaMeta();
	jokalaria.id = JOKOA_jokalariaIrudiaPersaonajea();
	obstakulua.id = JOKOA_jokalariaIrudiaPintxoak();
	obstakulua4.id = JOKOA_jokalariaIrudiaPintxoak();
	obstakulua5.id = JOKOA_jokalariaIrudiaPintxoak();
	obstakulua6.id = JOKOA_jokalariaIrudiaPintxoak();
	obstakulua7.id = JOKOA_jokalariaIrudiaPintxoak();
	obstakulua8.id = JOKOA_jokalariaIrudiaPintxoak();
	fuego.id = JOKOA_jokalariaIrudiaBala();
	kainon.id = JOKOA_jokalariaIrudiaKainoiaHori();

	//IRUDIEI POSIZIOA JARRI
	irudiaMugitu(fondo.id, fondo.pos.x, fondo.pos.y);
	irudiaMugitu(obstakulua.id, obstakulua.pos.x, obstakulua.pos.y);
	irudiaMugitu(obstakulua4.id, obstakulua4.pos.x, obstakulua4.pos.y);
	irudiaMugitu(obstakulua6.id, obstakulua6.pos.x, obstakulua6.pos.y);
	irudiaMugitu(obstakulua7.id, obstakulua7.pos.x, obstakulua7.pos.y);
	irudiaMugitu(obstakulua8.id, obstakulua8.pos.x, obstakulua8.pos.y);
	irudiaMugitu(kainon.id, kainon.pos.x, kainon.pos.y);
	irudiaMugitu(meta.id, meta.pos.x, meta.pos.y);
	irudiaMugitu(jokalaria.id, jokalaria.pos.x, jokalaria.pos.y);
	irudiakMarraztu();
	int i = 0, x = 0, j = 0;
	do {
		Sleep(2);
		pantailaGarbitu();
		fuego.pos.x = fuego.pos.x - 2;
		if (fuego.pos.x == 164)fuego.pos.x = 510;
		irudiaMugitu(fuego.id, fuego.pos.x, fuego.pos.y);
		j++;
		irudiaMugitu(fuego.id, fuego.pos.x, fuego.pos.y);
		irudiaMugitu(obstakulua5.id, obstakulua5.pos.x, obstakulua5.pos.y);
		irudiaMugitu(jokalaria.id, jokalaria.pos.x, jokalaria.pos.y);
		obstakulua5.pos.x = pintxoakMugitu(obstakulua5.pos.x, x);
		x++;
		if (x == 200)x = 0;
		irudiakMarraztu();

		//KARRATUAK SORTU ETA KOLISIOAK
		karratuaMarraztu(150, 400, 480, 455);
		jokalaria.pos.x = kolisioakDetektatuX(150, 400, 480, 455, jokalaria.pos.x, jokalaria.pos.y);
		jokalaria.pos.y = kolisioakDetektatuY(150, 400, 480, 455, jokalaria.pos.x, jokalaria.pos.y);
		arkatzKoloreaEzarri(255, 255, 255);
		karratuaMarraztu(420, 370, 450, 400);
		jokalaria.pos.x = kolisioakDetektatuX(420, 370, 450, 400, jokalaria.pos.x, jokalaria.pos.y);
		jokalaria.pos.y = kolisioakDetektatuY(420, 370, 450, 400, jokalaria.pos.x, jokalaria.pos.y);
		arkatzKoloreaEzarri(255, 255, 255);
		karratuaMarraztu(450, 150, 480, 455);
		jokalaria.pos.x = kolisioakDetektatuX(450, 150, 480, 455, jokalaria.pos.x, jokalaria.pos.y);
		jokalaria.pos.y = kolisioakDetektatuY(450, 150, 480, 455, jokalaria.pos.x, jokalaria.pos.y);
		arkatzKoloreaEzarri(255, 255, 255);
		karratuaMarraztu(210, 150, 480, 170);
		jokalaria.pos.x = kolisioakDetektatuX(210, 150, 480, 170, jokalaria.pos.x, jokalaria.pos.y);
		jokalaria.pos.y = kolisioakDetektatuY(210, 150, 480, 170, jokalaria.pos.x, jokalaria.pos.y);
		arkatzKoloreaEzarri(255, 255, 255);
		karratuaMarraztu(150, 290, 400, 310);
		jokalaria.pos.x = kolisioakDetektatuX(150, 290, 400, 310, jokalaria.pos.x, jokalaria.pos.y);
		jokalaria.pos.y = kolisioakDetektatuY(150, 290, 400, 310, jokalaria.pos.x, jokalaria.pos.y);
		arkatzKoloreaEzarri(255, 255, 255);
		karratuaMarraztu(150, 0, 170, 310);
		jokalaria.pos.x = kolisioakDetektatuX(150, 0, 170, 310, jokalaria.pos.x, jokalaria.pos.y);
		jokalaria.pos.y = kolisioakDetektatuY(150, 0, 170, 310, jokalaria.pos.x, jokalaria.pos.y);
		arkatzKoloreaEzarri(255, 255, 255);
		karratuaMarraztu(170, 225, 200, 310);
		jokalaria.pos.x = kolisioakDetektatuX(170, 225, 200, 310, jokalaria.pos.x, jokalaria.pos.y);
		jokalaria.pos.y = kolisioakDetektatuY(170, 225, 200, 310, jokalaria.pos.x, jokalaria.pos.y);
		arkatzKoloreaEzarri(255, 255, 255);
		pantailaBerriztu();

		//PERTSONAIAREN MUGIMENDUA
		ebentu = ebentuaJasoGertatuBada();
		if (ebentu == TECLA_RIGHT || ebentu == TECLA_LEFT)
		{
			if (ebentu == TECLA_RIGHT)
			{
				jokalaria.pos.x = jokalaria.pos.x + 12;
			}
			else
			{
				jokalaria.pos.x = jokalaria.pos.x - 12;
			}
		}

		if ((ebentu == TECLA_SPACE) && (i == 0))i = 1;
		if ((i > 0) && (i < 10))
		{
			jokalaria.pos.y = jokalaria.pos.y - 13;
			i++;
		}
		if ((i >= 10) && (i < 50))
		{
			jokalaria.pos.y++;
			i++;
		}
		if (i == 50)i = 0;
		if (i == 50)i = 0;
		jokalaria.pos.y = jokalaria.pos.y + 2;
		if (jokalaria.pos.y > 423)jokalaria.pos.y = 423;

		//PERTSONAIA ETA OBSTAKULUEN ARTEKO KOLISIOAK
		egoera = JOKOA_egoera(jokalaria, obstakulua);
		egoera2 = JOKOA_egoera(jokalaria, obstakulua4);
		egoera3 = JOKOA_egoera(jokalaria, obstakulua5);
		egoera4 = JOKOA_egoera(jokalaria, obstakulua6);
		egoera5 = JOKOA_egoera(jokalaria, fuego);
		egoera6 = JOKOA_egoera(jokalaria, obstakulua8);
		egoera7 = JOKOA_egoera(jokalaria, obstakulua7);

		if (jokalaria.pos.x > meta.pos.x - 20 && jokalaria.pos.x <meta.pos.x + 20 && jokalaria.pos.y >meta.pos.y - 20 && jokalaria.pos.y < meta.pos.y + 20)
		{
			irudiaKendu(jokalaria.id);
			irudiaKendu(obstakulua.id);
			irudiaKendu(obstakulua4.id);
			irudiaKendu(obstakulua5.id);
			irudiaKendu(obstakulua6.id);
			irudiaKendu(obstakulua7.id);
			irudiaKendu(obstakulua8.id);
			irudiaKendu(meta.id);
			irudiaKendu(fondo.id);
			irudiaKendu(fuego.id);
			irudiaKendu(kainon.id);
			jokatu4();
		}
	} while ((egoera == JOLASTEN) && (egoera7 == JOLASTEN) && (egoera2 == JOLASTEN) && (egoera3 == JOLASTEN) && (egoera4 == JOLASTEN) && (egoera5 == JOLASTEN) && (egoera6 == JOLASTEN));
	irudiaKendu(jokalaria.id);
	irudiaKendu(obstakulua.id);
	irudiaKendu(obstakulua4.id);
	irudiaKendu(obstakulua5.id);
	irudiaKendu(obstakulua6.id);
	irudiaKendu(obstakulua7.id);
	irudiaKendu(obstakulua8.id);
	irudiaKendu(meta.id);
	irudiaKendu(fondo.id);
	irudiaKendu(fuego.id);
	irudiaKendu(kainon.id);
	jokatu3();

	return egoera;
}

EGOERA jokatu4(void)
{
	int mugitu = 0; //boolean
	EGOERA  egoera = JOLASTEN, egoera1 = JOLASTEN;
	int ebentu = 0;
	JOKO_ELEMENTUA  jokalaria,  obstakulua, obstakulua1, fondo, meta;

	//Uint32 time01 = SDL_GetTicks(), time02;

	//JOKOKO ELEMENTUEN POSIZIOAK
	jokalaria.pos.x = 0;
	jokalaria.pos.y = 425;

	obstakulua.pos.x = 180;
	obstakulua.pos.y = 290;

	obstakulua1.pos.x = 120;
	obstakulua1.pos.y = 435;

	fondo.pos.x = 0;
	fondo.pos.y = 20;

	meta.pos.x = 10;
	meta.pos.y = 5;

	//IRUDIAK KARGATU
	fondo.id = JOKOA_jokalariaIrudiaFondo();
	meta.id = JOKOA_jokalariaIrudiaMeta();
	jokalaria.id = JOKOA_jokalariaIrudiaPersaonajea();
	obstakulua.id = JOKOA_jokalariaIrudiaPintxoak();
	obstakulua1.id = JOKOA_jokalariaIrudiaPintxoLuzi();

	//IRUDIEI POSIZIOA JARRI
	irudiaMugitu(fondo.id, fondo.pos.x, fondo.pos.y);
	irudiaMugitu(obstakulua.id, obstakulua.pos.x, obstakulua.pos.y);
	irudiaMugitu(obstakulua1.id, obstakulua1.pos.x, obstakulua1.pos.y);
	irudiaMugitu(meta.id, meta.pos.x, meta.pos.y);
	irudiakMarraztu();
	int i = 0;
	do {
		Sleep(4);
		pantailaGarbitu();
		irudiaMugitu(jokalaria.id, jokalaria.pos.x, jokalaria.pos.y);
		irudiakMarraztu();

		//KARRATUAK SORTU ETA KOLISIOAK
		karratuaMarraztu(60, 410, 100, 435);
		jokalaria.pos.x = kolisioakDetektatuX(60, 410, 100, 435, jokalaria.pos.x, jokalaria.pos.y);
		jokalaria.pos.y = kolisioakDetektatuY(60, 410, 100, 435, jokalaria.pos.x, jokalaria.pos.y);
		arkatzKoloreaEzarri(255, 255, 255);
		karratuaMarraztu(130, 370, 160, 455);
		jokalaria.pos.x = kolisioakDetektatuX(130, 370, 160, 455, jokalaria.pos.x, jokalaria.pos.y);
		jokalaria.pos.y = kolisioakDetektatuY(130, 370, 160, 455, jokalaria.pos.x, jokalaria.pos.y);
		karratuaMarraztu(160, 310, 220, 330);
		jokalaria.pos.x = kolisioakDetektatuX(160, 310, 220, 330, jokalaria.pos.x, jokalaria.pos.y);
		jokalaria.pos.y = kolisioakDetektatuY(160, 310, 220, 330, jokalaria.pos.x, jokalaria.pos.y);
		karratuaMarraztu(260, 350, 300, 380);
		jokalaria.pos.x = kolisioakDetektatuX(260, 350, 300, 380, jokalaria.pos.x, jokalaria.pos.y);
		jokalaria.pos.y = kolisioakDetektatuY(260, 350, 300, 380, jokalaria.pos.x, jokalaria.pos.y);
		karratuaMarraztu(330, 300, 350, 320);	
		jokalaria.pos.x = kolisioakDetektatuX(330, 300, 350, 320, jokalaria.pos.x, jokalaria.pos.y);
		jokalaria.pos.y = kolisioakDetektatuY(330, 300, 350, 320, jokalaria.pos.x, jokalaria.pos.y);
		karratuaMarraztu(340, 400, 380, 420);
		jokalaria.pos.x = kolisioakDetektatuX(340, 400, 380, 420, jokalaria.pos.x, jokalaria.pos.y);
		jokalaria.pos.y = kolisioakDetektatuY(340, 400, 380, 420, jokalaria.pos.x, jokalaria.pos.y);
		karratuaMarraztu(0, 50, 500, 70);
		jokalaria.pos.x = kolisioakDetektatuX(0, 50, 500, 70, jokalaria.pos.x, jokalaria.pos.y);
		jokalaria.pos.y = kolisioakDetektatuY(0, 50, 500, 70, jokalaria.pos.x, jokalaria.pos.y);
		karratuaMarraztu(410, 300, 440, 320);	
		jokalaria.pos.x = kolisioakDetektatuX(410, 300, 440, 320, jokalaria.pos.x, jokalaria.pos.y);
		jokalaria.pos.y = kolisioakDetektatuY(410, 300, 440, 320, jokalaria.pos.x, jokalaria.pos.y);
		karratuaMarraztu(500, 360, 520, 380);
		jokalaria.pos.x = kolisioakDetektatuX(500, 360, 520, 380, jokalaria.pos.x, jokalaria.pos.y);
		jokalaria.pos.y = kolisioakDetektatuY(500, 360, 520, 380, jokalaria.pos.x, jokalaria.pos.y);
		karratuaMarraztu(540, 300, 560, 320);
		jokalaria.pos.x = kolisioakDetektatuX(540, 300, 560, 320, jokalaria.pos.x, jokalaria.pos.y);
		jokalaria.pos.y = kolisioakDetektatuY(540, 300, 560, 320, jokalaria.pos.x, jokalaria.pos.y);
		karratuaMarraztu(500, 240, 520, 260);
		jokalaria.pos.x = kolisioakDetektatuX(500, 240, 520, 260, jokalaria.pos.x, jokalaria.pos.y);
		jokalaria.pos.y = kolisioakDetektatuY(500, 240, 520, 260, jokalaria.pos.x, jokalaria.pos.y);
		karratuaMarraztu(580, 240, 600, 260);
		jokalaria.pos.x = kolisioakDetektatuX(580, 240, 600, 260, jokalaria.pos.x, jokalaria.pos.y);
		jokalaria.pos.y = kolisioakDetektatuY(580, 240, 600, 260, jokalaria.pos.x, jokalaria.pos.y);
		karratuaMarraztu(540, 180, 560, 200);
		jokalaria.pos.x = kolisioakDetektatuX(540, 180, 560, 200, jokalaria.pos.x, jokalaria.pos.y);
		jokalaria.pos.y = kolisioakDetektatuY(540, 180, 560, 200, jokalaria.pos.x, jokalaria.pos.y);
		karratuaMarraztu(600, 120, 620, 140);
		jokalaria.pos.x = kolisioakDetektatuX(600, 120, 620, 140, jokalaria.pos.x, jokalaria.pos.y);
		jokalaria.pos.y = kolisioakDetektatuY(600, 120, 620, 140, jokalaria.pos.x, jokalaria.pos.y);
		karratuaMarraztu(520, 80, 540, 100);
		jokalaria.pos.x = kolisioakDetektatuX(520, 80, 540, 100, jokalaria.pos.x, jokalaria.pos.y);
		jokalaria.pos.y = kolisioakDetektatuY(520, 80, 540, 100, jokalaria.pos.x, jokalaria.pos.y);
		pantailaBerriztu();

		//PERTSONAIAREN MUGIMENDUA
		ebentu = ebentuaJasoGertatuBada();
		if (ebentu == TECLA_RIGHT || ebentu == TECLA_LEFT)
		{
			if (ebentu == TECLA_RIGHT)
			{
				jokalaria.pos.x = jokalaria.pos.x + 12;
			}
			else
			{
				jokalaria.pos.x = jokalaria.pos.x - 12;
			}
		}

		if ((ebentu == TECLA_SPACE) && (i == 0))i = 1;
		if ((i > 0) && (i < 10))
		{
			jokalaria.pos.y = jokalaria.pos.y - 12;
			i++;
		}
		if ((i >= 10) && (i < 50))
		{
			jokalaria.pos.y++;
			i++;
		}
		if (i == 50)i = 0;
		
		jokalaria.pos.y = jokalaria.pos.y + 2;
		if (jokalaria.pos.y > 423)jokalaria.pos.y = 423;

		//PERTSONAIA ETA OBSTAKULUEN ARTEKO KOLISIOAK
		egoera = JOKOA_egoera(jokalaria, obstakulua);
		egoera1 = JOKOA_egoeraPintxoluzi(jokalaria, obstakulua1);
	
		if (jokalaria.pos.x > meta.pos.x - 20 && jokalaria.pos.x <meta.pos.x + 20 && jokalaria.pos.y >meta.pos.y - 20 && jokalaria.pos.y < meta.pos.y + 20)
		{
			irudiaKendu(jokalaria.id);
			irudiaKendu(meta.id);
			irudiaKendu(fondo.id);
			irudiaKendu(obstakulua.id);
			irudiaKendu(obstakulua1.id);
			jokatu5();
		}
	} while ((egoera == JOLASTEN)&&(egoera1 == JOLASTEN));
	irudiaKendu(jokalaria.id);
	irudiaKendu(meta.id);
	irudiaKendu(fondo.id);
	irudiaKendu(obstakulua.id);
	irudiaKendu(obstakulua1.id);
	jokatu4();

	return egoera;
}


EGOERA jokatu5(void)
{
	int mugitu = 0; //boolean
	EGOERA  egoera = JOLASTEN, egoera1 = JOLASTEN, egoera2 = JOLASTEN, egoera3 = JOLASTEN, egoera4 = JOLASTEN, egoera5 = JOLASTEN, egoera6 = JOLASTEN;
	int ebentu = 0;
	JOKO_ELEMENTUA  jokalaria, zerra, obstakulua, obstakulua4, obstakulua5, obstakulua6, obstakulua7, obstakulua8, fondo, meta;

	//Uint32 time01 = SDL_GetTicks(), time02;

	//JOKOKO ELEMENTUEN POSIZIOAK
	jokalaria.pos.x = 0;
	jokalaria.pos.y = 425;

	zerra.pos.x = 200;
	zerra.pos.y = 310;

	obstakulua.pos.x = 200;
	obstakulua.pos.y = 100;

	obstakulua4.pos.x = 300;
	obstakulua4.pos.y = 100;

	obstakulua5.pos.x = 330;
	obstakulua5.pos.y = 250;


	obstakulua6.pos.x = 600;
	obstakulua6.pos.y = 280;

	obstakulua7.pos.x = 305;
	obstakulua7.pos.y = 380;

	obstakulua8.pos.x = 560;
	obstakulua8.pos.y = 180;

	fondo.pos.x = 0;
	fondo.pos.y = 20;

	meta.pos.x = 180;
	meta.pos.y = 215;

	//IRUDIAK KARGATU
	fondo.id = JOKOA_jokalariaIrudiaFondo();
	meta.id = JOKOA_jokalariaIrudiaMeta();
	jokalaria.id = JOKOA_jokalariaIrudiaPersaonajea();
	obstakulua.id = JOKOA_jokalariaIrudiaPintxoak();
	obstakulua4.id = JOKOA_jokalariaIrudiaPintxoak();
	obstakulua5.id = JOKOA_jokalariaIrudiaPintxoak();
	obstakulua6.id = JOKOA_jokalariaIrudiaPintxoak();
	obstakulua7.id = JOKOA_jokalariaIrudiaPintxoak();
	obstakulua8.id = JOKOA_jokalariaIrudiaPintxoak();
	zerra.id = JOKOA_jokalariaIrudiaZerra();

	//IRUDIEI POSIZIOA JARRI
	irudiaMugitu(fondo.id, fondo.pos.x, fondo.pos.y);
	irudiaMugitu(obstakulua5.id, obstakulua5.pos.x, obstakulua5.pos.y);
	irudiaMugitu(obstakulua6.id, obstakulua6.pos.x, obstakulua6.pos.y);
	irudiaMugitu(obstakulua8.id, obstakulua8.pos.x, obstakulua8.pos.y);

	irudiaMugitu(meta.id, meta.pos.x, meta.pos.y);
	irudiakMarraztu();
	int i = 0, x = 0, k = 0;
	do {
		Sleep(2);
		pantailaGarbitu();
		irudiaMugitu(zerra.id, zerra.pos.x, zerra.pos.y);
		zerra.pos.x = serraBertikal(zerra.pos.x, k);
		k = k + 2;
		if (k == 250)k = 0;
		obstakulua4.pos.x = pintxoakMugitu(obstakulua4.pos.x, x);
		obstakulua.pos.x = pintxoakMugitu(obstakulua.pos.x, x);
		obstakulua7.pos.x = pintxoakMugitu(obstakulua7.pos.x, x);
		x++;
		if (x == 200)x = 0;
		irudiaMugitu(obstakulua.id, obstakulua.pos.x, obstakulua.pos.y);
		irudiaMugitu(obstakulua4.id, obstakulua4.pos.x, obstakulua4.pos.y);
		irudiaMugitu(obstakulua7.id, obstakulua7.pos.x, obstakulua7.pos.y);
		irudiaMugitu(jokalaria.id, jokalaria.pos.x, jokalaria.pos.y);
		irudiakMarraztu();

		//KARRATUAK SORTU ETA KOLISIOAK
		karratuaMarraztu(160, 120, 180, 455);
		arkatzKoloreaEzarri(255, 255, 255);
		jokalaria.pos.x = kolisioakDetektatuX(160, 120, 180, 455, jokalaria.pos.x, jokalaria.pos.y);
		jokalaria.pos.y = kolisioakDetektatuY(160, 120, 180, 455, jokalaria.pos.x, jokalaria.pos.y);
		karratuaMarraztu(180, 120, 500, 140);
		jokalaria.pos.x = kolisioakDetektatuX(180, 120, 500, 140, jokalaria.pos.x, jokalaria.pos.y);
		jokalaria.pos.y = kolisioakDetektatuY(180, 120, 500, 140, jokalaria.pos.x, jokalaria.pos.y);
		karratuaMarraztu(480, 140, 500, 400);
		jokalaria.pos.x = kolisioakDetektatuX(480, 140, 500, 400, jokalaria.pos.x, jokalaria.pos.y);
		jokalaria.pos.y = kolisioakDetektatuY(480, 140, 500, 400, jokalaria.pos.x, jokalaria.pos.y);
		karratuaMarraztu(500, 200, 600, 220);
		jokalaria.pos.x = kolisioakDetektatuX(500, 200, 600, 220, jokalaria.pos.x, jokalaria.pos.y);
		jokalaria.pos.y = kolisioakDetektatuY(500, 200, 600, 220, jokalaria.pos.x, jokalaria.pos.y);
		karratuaMarraztu(550, 300, 650, 320);
		jokalaria.pos.x = kolisioakDetektatuX(550, 300, 650, 320, jokalaria.pos.x, jokalaria.pos.y);
		jokalaria.pos.y = kolisioakDetektatuY(550, 300, 650, 320, jokalaria.pos.x, jokalaria.pos.y);
		karratuaMarraztu(180, 260, 400, 280);
		jokalaria.pos.x = kolisioakDetektatuX(180, 260, 400, 280, jokalaria.pos.x, jokalaria.pos.y);
		jokalaria.pos.y = kolisioakDetektatuY(180, 260, 400, 280, jokalaria.pos.x, jokalaria.pos.y);
		karratuaMarraztu(250, 400, 500, 420);
		jokalaria.pos.x = kolisioakDetektatuX(250, 400, 500, 420, jokalaria.pos.x, jokalaria.pos.y);
		jokalaria.pos.y = kolisioakDetektatuY(250, 400, 500, 420, jokalaria.pos.x, jokalaria.pos.y);
		karratuaMarraztu(460, 320, 480, 340);
		jokalaria.pos.x = kolisioakDetektatuX(460, 320, 480, 340, jokalaria.pos.x, jokalaria.pos.y);
		jokalaria.pos.y = kolisioakDetektatuY(460, 320, 480, 340, jokalaria.pos.x, jokalaria.pos.y);
		karratuaMarraztu(140, 380, 160, 400);
		jokalaria.pos.x = kolisioakDetektatuX(140, 380, 160, 400, jokalaria.pos.x, jokalaria.pos.y);
		jokalaria.pos.y = kolisioakDetektatuY(140, 380, 160, 400, jokalaria.pos.x, jokalaria.pos.y);
		karratuaMarraztu(80, 290, 100, 310);
		jokalaria.pos.x = kolisioakDetektatuX(80, 290, 100, 310, jokalaria.pos.x, jokalaria.pos.y);
		jokalaria.pos.y = kolisioakDetektatuY(80, 290, 100, 310, jokalaria.pos.x, jokalaria.pos.y);
		karratuaMarraztu(80, 220, 100, 240);
		jokalaria.pos.x = kolisioakDetektatuX(80, 220, 100, 240, jokalaria.pos.x, jokalaria.pos.y);
		jokalaria.pos.y = kolisioakDetektatuY(80, 220, 100, 240, jokalaria.pos.x, jokalaria.pos.y);
		karratuaMarraztu(80, 150, 100, 170);
		jokalaria.pos.x = kolisioakDetektatuX(80, 150, 100, 170, jokalaria.pos.x, jokalaria.pos.y);
		jokalaria.pos.y = kolisioakDetektatuY(80, 150, 100, 170, jokalaria.pos.x, jokalaria.pos.y);
		pantailaBerriztu();

		//PERTSONAIAREN MUGIMENDUA
		ebentu = ebentuaJasoGertatuBada();
		if (ebentu == TECLA_RIGHT || ebentu == TECLA_LEFT)
		{
			if (ebentu == TECLA_RIGHT)
			{
				jokalaria.pos.x = jokalaria.pos.x + 12;
			}
			else
			{
				jokalaria.pos.x = jokalaria.pos.x - 15;
			}
		}

		if ((ebentu == TECLA_SPACE) && (i == 0))i = 1;
		if ((i > 0) && (i < 10))
		{
			jokalaria.pos.y = jokalaria.pos.y - 13;
			i++;
		}
		if ((i >= 10) && (i < 50))
		{
			jokalaria.pos.y++;
			i++;
		}
		if (i == 50)i = 0;
		jokalaria.pos.y = jokalaria.pos.y + 2;
		if (jokalaria.pos.y > 423)jokalaria.pos.y = 423;

		//PERTSONAIA ETA OBSTAKULUEN ARTEKO KOLISIOAK
		egoera = JOKOA_egoera(jokalaria, obstakulua);
		egoera1 = JOKOA_egoeraZerra(jokalaria, zerra);
		egoera2 = JOKOA_egoera(jokalaria, obstakulua4);
		egoera3 = JOKOA_egoera(jokalaria, obstakulua5);
		egoera4 = JOKOA_egoera(jokalaria, obstakulua6);
		egoera5 = JOKOA_egoera(jokalaria, obstakulua7);
		egoera6 = JOKOA_egoera(jokalaria, obstakulua8);

		if (jokalaria.pos.x > meta.pos.x - 20 && jokalaria.pos.x <meta.pos.x + 20 && jokalaria.pos.y >meta.pos.y - 20 && jokalaria.pos.y < meta.pos.y + 20)
		{
			irudiaKendu(jokalaria.id);
			irudiaKendu(obstakulua.id);
			irudiaKendu(obstakulua4.id);
			irudiaKendu(obstakulua5.id);
			irudiaKendu(obstakulua6.id);
			irudiaKendu(obstakulua7.id);
			irudiaKendu(obstakulua8.id);
			irudiaKendu(zerra.id);
			irudiaKendu(meta.id);
			irudiaKendu(fondo.id);
			jokatu6();
		}
	} while ((egoera == JOLASTEN) && (egoera1 == JOLASTEN) && (egoera2 == JOLASTEN) && (egoera3 == JOLASTEN) && (egoera4 == JOLASTEN) && (egoera5 == JOLASTEN) && (egoera6 == JOLASTEN));
	irudiaKendu(jokalaria.id);
	irudiaKendu(obstakulua.id);
	irudiaKendu(obstakulua4.id);
	irudiaKendu(obstakulua5.id);
	irudiaKendu(obstakulua6.id);
	irudiaKendu(obstakulua7.id);
	irudiaKendu(obstakulua8.id);
	irudiaKendu(zerra.id);
	irudiaKendu(meta.id);
	irudiaKendu(fondo.id);
	jokatu5();

	return egoera;
}

EGOERA jokatu6(void)
{
	int mugitu = 0; //boolean
	EGOERA  egoera = JOLASTEN, egoera6 = JOLASTEN, egoera7 = JOLASTEN, egoera1 = JOLASTEN, egoera2 = JOLASTEN, egoera3 = JOLASTEN, egoera4 = JOLASTEN, egoera5 = JOLASTEN;
	int ebentu = 0;
	JOKO_ELEMENTUA  jokalaria, zerra, bukaera, kainoia, fuego, kaiñon, obstakulua, obstakulua4, obstakulua5, obstakulua6, obstakulua7, fondo, meta;

	//Uint32 time01 = SDL_GetTicks(), time02;


	//JOKOKO ELEMENTUEN POSIZIOAK
	jokalaria.pos.x = 0;
	jokalaria.pos.y = 425;

	kaiñon.pos.x = 370;
	kaiñon.pos.y = 0;

	obstakulua.pos.x = 200;
	obstakulua.pos.y = 435;

	bukaera.pos.x = 200;
	bukaera.pos.y = 435;

	fuego.pos.x = 485;
	fuego.pos.y = 170;

	obstakulua4.pos.x = 325;
	obstakulua4.pos.y = 435;

	obstakulua5.pos.x = 370;
	obstakulua5.pos.y = 270;


	obstakulua6.pos.x = 240;
	obstakulua6.pos.y = 270;

	obstakulua7.pos.x = 185;
	obstakulua7.pos.y = 270;

	fondo.pos.x = 0;
	fondo.pos.y = 20;

	meta.pos.x = 10;
	meta.pos.y = 240;

	zerra.pos.x = 100;
	zerra.pos.y = 170;

	kainoia.pos.x = 100;
	kainoia.pos.y = 200;

	//IRUDIAK KARGATU
	fondo.id = JOKOA_jokalariaIrudiaFondo();
	meta.id = JOKOA_jokalariaIrudiaMeta();
	jokalaria.id = JOKOA_jokalariaIrudiaPersaonajea();
	kaiñon.id = JOKOA_jokalariaIrudiaKainoiaBert();
	fuego.id = JOKOA_jokalariaIrudiaBala();
	obstakulua.id = JOKOA_jokalariaIrudiaPintxoak();
	obstakulua4.id = JOKOA_jokalariaIrudiaPintxoak();
	obstakulua5.id = JOKOA_jokalariaIrudiaPintxoak();
	obstakulua6.id = JOKOA_jokalariaIrudiaPintxoak();
	obstakulua7.id = JOKOA_jokalariaIrudiaPintxoak();
	zerra.id = JOKOA_jokalariaIrudiaZerra();
	kainoia.id = JOKOA_jokalariaIrudiaZerra();


	//IRUDIEI POSIZIOA JARRI
	irudiaMugitu(fondo.id, fondo.pos.x, fondo.pos.y);
	irudiaMugitu(kaiñon.id, kaiñon.pos.x, kaiñon.pos.y);
	irudiaMugitu(obstakulua.id, obstakulua.pos.x, obstakulua.pos.y);
	irudiaMugitu(obstakulua5.id, obstakulua5.pos.x, obstakulua5.pos.y);
	irudiaMugitu(obstakulua7.id, obstakulua7.pos.x, obstakulua7.pos.y);
	irudiaMugitu(zerra.id, zerra.pos.x, zerra.pos.y);
	irudiaMugitu(kainoia.id, kainoia.pos.x, kainoia.pos.y);
	irudiaMugitu(meta.id, meta.pos.x, meta.pos.y);
	irudiakMarraztu();
	int i = 0, x = 0, j = 0;
	do {
		Sleep(2);
		pantailaGarbitu();

		//ZERRAREN MUGIMENDUA
		zerra.pos.y = serraBertikal(zerra.pos.y, j);
		irudiaMugitu(zerra.id, zerra.pos.x, zerra.pos.y);
		kainoia.pos.x = serraHorizontal(kainoia.pos.x, j);
		irudiaMugitu(kainoia.id, kainoia.pos.x, kainoia.pos.y);

		//SUAREN MUGIMENDUA
		fuego.pos.y++;
		if (fuego.pos.y == 300)fuego.pos.y = 170;
		irudiaMugitu(fuego.id, fuego.pos.x, fuego.pos.y);
		j++;
		if (j == 250)j = 0;

		//PINTXOEN MUGIMENDUA
		irudiaMugitu(obstakulua4.id, obstakulua4.pos.x, obstakulua4.pos.y);
		irudiaMugitu(obstakulua6.id, obstakulua6.pos.x, obstakulua6.pos.y);
		obstakulua4.pos.x = pintxoakMugitu(obstakulua4.pos.x, x);
		obstakulua6.pos.x = pintxoakMugitu(obstakulua6.pos.x, x);
		x++;
		if (x == 200)x = 0;
		irudiaMugitu(jokalaria.id, jokalaria.pos.x, jokalaria.pos.y);
		irudiakMarraztu();

		//KARRATUAK SORTU ETA KOLISIOAK
		karratuaMarraztu(455, 0, 555, 73);
		arkatzKoloreaEzarri(255, 255, 255);
		karratuaMarraztu(580, 385, 630, 455);
		jokalaria.pos.x = kolisioakDetektatuX(580, 385, 630, 455, jokalaria.pos.x, jokalaria.pos.y);
		jokalaria.pos.y = kolisioakDetektatuY(580, 385, 630, 455, jokalaria.pos.x, jokalaria.pos.y);
		arkatzKoloreaEzarri(255, 255, 255);
		karratuaMarraztu(485, 335, 535, 395);
		jokalaria.pos.x = kolisioakDetektatuX(485, 335, 535, 395, jokalaria.pos.x, jokalaria.pos.y);
		jokalaria.pos.y = kolisioakDetektatuY(485, 335, 535, 395, jokalaria.pos.x, jokalaria.pos.y);
		arkatzKoloreaEzarri(255, 255, 255);
		karratuaMarraztu(160, 290, 435, 330);
		jokalaria.pos.x = kolisioakDetektatuX(160, 290, 435, 330, jokalaria.pos.x, jokalaria.pos.y);
		jokalaria.pos.y = kolisioakDetektatuY(160, 290, 435, 330, jokalaria.pos.x, jokalaria.pos.y);
		arkatzKoloreaEzarri(255, 255, 255);
		karratuaMarraztu(20, 285, 80, 350);
		jokalaria.pos.x = kolisioakDetektatuX(20, 285, 80, 350, jokalaria.pos.x, jokalaria.pos.y);
		jokalaria.pos.y = kolisioakDetektatuY(20, 285, 80, 350, jokalaria.pos.x, jokalaria.pos.y);
		arkatzKoloreaEzarri(255, 255, 255);
		pantailaBerriztu();

		//PERTSONAIAREN MUGIMENDUA
		ebentu = ebentuaJasoGertatuBada();
		if (ebentu == TECLA_RIGHT || ebentu == TECLA_LEFT)
		{
			if (ebentu == TECLA_RIGHT)
			{
				jokalaria.pos.x = jokalaria.pos.x + 12;
			}
			else
			{
				jokalaria.pos.x = jokalaria.pos.x - 13;
			}
		}

		if ((ebentu == TECLA_SPACE) && (i == 0))i = 1;
		if ((i > 0) && (i < 10))
		{
			jokalaria.pos.y = jokalaria.pos.y - 14;
			i++;
		}
		if ((i >= 10) && (i < 50))
		{
			jokalaria.pos.y++;
			i++;
		}
		if (i == 50)i = 0;

		jokalaria.pos.y = jokalaria.pos.y + 2;
		if (jokalaria.pos.y > 423)jokalaria.pos.y = 423;
		if (jokalaria.pos.x < 0)jokalaria.pos.x = 0;
		//PERTSONAIA ETA OBSTAKULUEN ARTEKO KOLISIOAK
		egoera = JOKOA_egoera(jokalaria, obstakulua);
		egoera1 = JOKOA_egoera(jokalaria, fuego);
		egoera2 = JOKOA_egoera(jokalaria, obstakulua4);
		egoera3 = JOKOA_egoera(jokalaria, obstakulua5);
		egoera4 = JOKOA_egoera(jokalaria, obstakulua6);
		egoera5 = JOKOA_egoera(jokalaria, obstakulua7);
		egoera6 = JOKOA_egoera(jokalaria, zerra);
		egoera7 = JOKOA_egoera(jokalaria, kainoia);
		
		if (jokalaria.pos.x > meta.pos.x - 20 && jokalaria.pos.x <meta.pos.x + 20 && jokalaria.pos.y >meta.pos.y - 20 && jokalaria.pos.y < meta.pos.y + 20)
		{
			irudiaKendu(jokalaria.id);
			irudiaKendu(obstakulua.id);
			irudiaKendu(obstakulua4.id);
			irudiaKendu(obstakulua5.id);
			irudiaKendu(obstakulua6.id);
			irudiaKendu(obstakulua7.id);
			irudiaKendu(zerra.id);
			irudiaKendu(fuego.id);
			irudiaKendu(meta.id);
			irudiaKendu(fondo.id);
			irudiaKendu(kainoia.id);
			irudiaKendu(kaiñon.id);
			while(i<200)
			{
				bukaera.id = JOKOA_IrudiaBukaera();
				irudiaMugitu(bukaera.id, bukaera.pos.x, bukaera.pos.y);
			i++;
			}
			irudiaKendu(bukaera.id);
			sgItxi();
		}
	} while ((egoera == JOLASTEN) && (egoera1 == JOLASTEN) && (egoera6 == JOLASTEN) && (egoera7 == JOLASTEN) && (egoera2 == JOLASTEN) && (egoera3 == JOLASTEN) && (egoera4 == JOLASTEN) && (egoera5 == JOLASTEN));
	irudiaKendu(jokalaria.id);
	irudiaKendu(obstakulua.id);
	irudiaKendu(obstakulua4.id);
	irudiaKendu(obstakulua5.id);
	irudiaKendu(obstakulua6.id);
	irudiaKendu(obstakulua7.id);
	irudiaKendu(zerra.id);
	irudiaKendu(meta.id);
	irudiaKendu(fondo.id);
	irudiaKendu(kainoia.id);
	irudiaKendu(kaiñon.id);
	irudiaKendu(fuego.id);
	jokatu6();
}


//KOLIZIOA PINTXOAK
EGOERA JOKOA_egoera(JOKO_ELEMENTUA jokalaria, JOKO_ELEMENTUA oztopoa) {
	EGOERA  ret = JOLASTEN;
	if (jokalaria.pos.x > oztopoa.pos.x - 20 && jokalaria.pos.x <oztopoa.pos.x + 20 && jokalaria.pos.y >oztopoa.pos.y - 20 && jokalaria.pos.y < oztopoa.pos.y + 20) {
		ret = IRABAZI;
	}
	else if (jokalaria.pos.x > 600) {
		ret = GALDU;
	}
	return ret;
}
//KOLIZIOA ZERRA
EGOERA JOKOA_egoeraZerra(JOKO_ELEMENTUA jokalaria, JOKO_ELEMENTUA oztopoa) {
	EGOERA  ret = JOLASTEN;
	if (jokalaria.pos.x > oztopoa.pos.x - 20 && jokalaria.pos.x <oztopoa.pos.x + 20 && jokalaria.pos.y >oztopoa.pos.y - 33 && jokalaria.pos.y < oztopoa.pos.y + 33) {
		ret = IRABAZI;
	}
	else if (jokalaria.pos.x > 600) {
		ret = GALDU;
	}
	return ret;
}
//KOLIZIOA PINTXO LUZEA
EGOERA JOKOA_egoeraPintxoluzi(JOKO_ELEMENTUA jokalaria, JOKO_ELEMENTUA oztopoa) {
	EGOERA  ret = JOLASTEN;
	if (jokalaria.pos.x > oztopoa.pos.x  && jokalaria.pos.x <oztopoa.pos.x + 520 && jokalaria.pos.y >oztopoa.pos.y - 20 && jokalaria.pos.y < oztopoa.pos.y + 20) {
		ret = IRABAZI;
	}
	else if (jokalaria.pos.x > 600) {
		ret = GALDU;
	}
	return ret;
}
//PINTXOAK MUGITZEKO FUNTZIOA
int pintxoakMugitu(int oX, int i)
{
	if (i < 100)
	{
		oX = oX + 1;
	}
	if (i >= 100)
	{
		oX = oX - 1;
	}
	return oX;
}
//ZERRAK MUGITZEKO FUNTZIOAK
int serraBertikal(int pY, int j)
{
	if (j < 124)
	{
		pY = pY + 2;
	}
	if (j >= 125)
	{
		pY = pY - 2;
	}
	return pY;
}
int serraHorizontal( int kX, int j)
{
	if (j < 125)
	{
		kX = kX + 2;
	}
	if (j >= 125)
	{
		kX = kX - 2;
	}
	return kX;
}

int kolisioakDetektatuX(int x1, int y1, int x2, int y2, int jokalariaX, int jokalariaY)
{
	if((jokalariaX < x2)&&(jokalariaX > x1-32)&&(jokalariaY > y1-32) && (jokalariaY < y2))
	{
		if ((jokalariaX < x1)&& (jokalariaX < x1-19))return x1-32;
		else if (jokalariaX > x2 - 13)return x2;
		else return jokalariaX;
	}
	else return jokalariaX;
}
int kolisioakDetektatuY(int x1, int y1, int x2, int y2, int jokalariaX, int jokalariaY)
{
	if ((jokalariaX < x2) && (jokalariaX > x1-32) && (jokalariaY > y1-32) && (jokalariaY < y2))
	{
		if (jokalariaY < y1)return y1-32;
		else if (jokalariaY > y2-32)return y2;
		else return jokalariaY;
	}
	else return jokalariaY;
}

int JOKOA_jokalariaIrudiaPersaonajea() 
{
  int martzianoId = -1;
  martzianoId = irudiaKargatu(".\\img\\personaje.bmp");
  irudiaMugitu(martzianoId, 10, 239);
  pantailaGarbitu();
  irudiakMarraztu();
  pantailaBerriztu();
  return martzianoId;

}

int JOKOA_jokalariaIrudiaFondo()
{
	int martzianoId = -1;
	martzianoId = irudiaKargatu(".\\img\\fondo.bmp");
	irudiaMugitu(martzianoId, 0, 0);
	pantailaGarbitu();
	irudiakMarraztu();
	pantailaBerriztu();
	return martzianoId;

}
int JOKOA_jokalariaIrudiaMeta()
{
	int martzianoId = -1;
	martzianoId = irudiaKargatu(".\\img\\meta.bmp");
	irudiaMugitu(martzianoId, 10, 239);
	pantailaGarbitu();
	irudiakMarraztu();
	pantailaBerriztu();
	return martzianoId;

}
int JOKOA_jokalariaIrudiaAmaiera()
{
	int martzianoId = -1;
	martzianoId = irudiaKargatu(".\\img\\bukaera.bmp");
	irudiaMugitu(martzianoId, 0, 0);
	pantailaGarbitu();
	irudiakMarraztu();
	pantailaBerriztu();
	return martzianoId;

}
int JOKOA_jokalariaIrudiaZerra()
{
	int martzianoId = -1;
	martzianoId = irudiaKargatu(".\\img\\piedra.bmp");
	irudiaMugitu(martzianoId, 10, 239);
	pantailaGarbitu();
	irudiakMarraztu();
	pantailaBerriztu();
	return martzianoId;

}
int JOKOA_jokalariaIrudiaBala()
{
	int martzianoId = -1;
	martzianoId = irudiaKargatu(".\\img\\fuego.bmp");
	irudiaMugitu(martzianoId, 10, 239);
	pantailaGarbitu();
	irudiakMarraztu();
	pantailaBerriztu();
	return martzianoId;

}
int JOKOA_jokalariaIrudiaKainoiaBert()
{
	int martzianoId = -1;
	martzianoId = irudiaKargatu(".\\img\\disparador.bmp");
	irudiaMugitu(martzianoId, 10, 239);
	pantailaGarbitu();
	irudiakMarraztu();
	pantailaBerriztu();
	return martzianoId;

}
int JOKOA_jokalariaIrudiaTutorial()
{
	int martzianoId = -1;
	martzianoId = irudiaKargatu(".\\img\\tutorial.bmp");
	irudiaMugitu(martzianoId, 10, 239);
	pantailaGarbitu();
	irudiakMarraztu();
	pantailaBerriztu();
	return martzianoId;

}

int JOKOA_jokalariaIrudiaPintxoak()
{
	int martzianoId = -1;
	martzianoId = irudiaKargatu(".\\img\\pintxo.bmp");
	irudiaMugitu(martzianoId, 10, 239);
	pantailaGarbitu();
	irudiakMarraztu();
	pantailaBerriztu();
	return martzianoId;

}
int JOKOA_jokalariaIrudiaPintxoLuzi()
{
	int martzianoId = -1;
	martzianoId = irudiaKargatu(".\\img\\pintxoluzi.bmp");
	irudiaMugitu(martzianoId, 10, 239);
	pantailaGarbitu();
	irudiakMarraztu();
	pantailaBerriztu();
	return martzianoId;

}

int JOKOA_jokalariaIrudiaPortada()
{
	int martzianoId = -1;
	martzianoId = irudiaKargatu(".\\img\\portada2.bmp");
	irudiaMugitu(martzianoId, 0, 0);
	pantailaGarbitu();
	irudiakMarraztu();
	pantailaBerriztu();
	return martzianoId;

}

int JOKOA_jokalariaIrudiaEzarpenak()
{
	int martzianoId = -1;
	martzianoId = irudiaKargatu(".\\img\\Ezarpenak2.bmp");
	irudiaMugitu(martzianoId, 0, 0);
	pantailaGarbitu();
	irudiakMarraztu();
	pantailaBerriztu();
	return martzianoId;

}
int JOKOA_jokalariaIrudiaKredituak()
{
	int martzianoId = -1;
	martzianoId = irudiaKargatu(".\\img\\Kredituak2.bmp");
	irudiaMugitu(martzianoId, 0, 0);
	pantailaGarbitu();
	irudiakMarraztu();
	pantailaBerriztu();
	return martzianoId;

}

int JOKOA_IrudiaBukaera()
{
	int martzianoId = -1;
	martzianoId = irudiaKargatu(".\\img\\bukaera.bmp");
	irudiaMugitu(martzianoId, 0, 0);
	pantailaGarbitu();
	irudiakMarraztu();
	pantailaBerriztu();
	return martzianoId;

}

int JOKOA_jokalariaIrudiaKainoiaHori()
{
	int martzianoId = -1;
	martzianoId = irudiaKargatu(".\\img\\disparadorh.bmp");
	irudiaMugitu(martzianoId, 0, 0);
	pantailaGarbitu();
	irudiakMarraztu();
	pantailaBerriztu();
	return martzianoId;

}
