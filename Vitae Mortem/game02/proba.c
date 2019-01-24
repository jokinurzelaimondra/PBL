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

void sarreraMezuaIdatzi();
int JOKOA_jokalariaIrudiaSortu();
//void zirkuluaBistaratu(int xRef, int yRef);
void JOKOA_lerroHBatMargotu(int x, int y, int x1, int y1);
void JOKOA_lerroVBatMargotu(int x, int y, int x1, int y1);
EGOERA JOKOA_egoera(JOKO_ELEMENTUA jokalaria, JOKO_ELEMENTUA oztopoa);
POSIZIOA ERREALITATE_FISIKOA_mugimendua(POSIZIOA posizioa);
//int  BUKAERA_menua(EGOERA egoera);
int BUKAERA_irudiaBistaratu();

void jokoaAurkeztu(void)
{
  int ebentu = 0;
  JOKO_ELEMENTUA hasiera, play;

  hasiera.id =JOKOA_jokalariaIrudiaSortu2();
  play.id = JOKOA_jokalariaIrudiaSortu3();
  do
  {
	
    ebentu = ebentuaJasoGertatuBada();
	  
  } while (ebentu != SAGU_BOTOIA_EZKERRA);
  irudiaKendu(hasiera.id);
  irudiaKendu(play.id);
  pantailaGarbitu();
  pantailaBerriztu();
  
}

void JokoarenMugimenduenAzalpena()
{
  textuaIdatzi(100, 200, "Sakatu eskuineko gezia aurrera joateko");
  pantailaBerriztu();
}

EGOERA jokatu(void) 
{
  int mugitu = 0; //boolean
  EGOERA  egoera = JOLASTEN;
  int ebentu = 0, ebentu1=0;
  JOKO_ELEMENTUA  jokalaria, obstakulua, fondo, meta;
  POSIZIOA aux;

  //Uint32 time01 = SDL_GetTicks(), time02;

  jokalaria.pos.x = 0;
  jokalaria.pos.y = 425;

  obstakulua.pos.x = 350;
  obstakulua.pos.y = 435;

  fondo.pos.x = 0;
  fondo.pos.y = 20;

  meta.pos.x = 580;
  meta.pos.y = 410;

  audioInit();
  loadTheMusic(JOKOA_SOUND);
  playMusic();
  fondo.id = JOKOA_jokalariaIrudiaSortu4();
  meta.id = JOKOA_jokalariaIrudiaSortu5();
  jokalaria.id = JOKOA_jokalariaIrudiaSortu();
  obstakulua.id = JOKOA_jokalariaIrudiaSortu1();
  irudiaMugitu(fondo.id, fondo.pos.x, fondo.pos.y);
  irudiaMugitu(obstakulua.id, obstakulua.pos.x, obstakulua.pos.y);
  irudiaMugitu(meta.id, meta.pos.x, meta.pos.y);
  irudiakMarraztu();
  do {
    Sleep(2);
    pantailaGarbitu();
    irudiaMugitu(jokalaria.id, jokalaria.pos.x, jokalaria.pos.y);
	irudiakMarraztu();
	ebentuaJasoGertatuBada(jokalaria.pos.x, jokalaria.pos.y);
    pantailaBerriztu();
    ebentu = ebentuaJasoGertatuBada();
	if (ebentu == TECLA_RIGHT || ebentu == TECLA_LEFT)
	{
		if (ebentu == TECLA_RIGHT)
		{
			jokalaria.pos.x = jokalaria.pos.x + 12;
		}

		if (ebentu == TECLA_LEFT)
		{
			jokalaria.pos.x = jokalaria.pos.x - 12;
		}
	}

	if (ebentu == TECLA_SPACE || ebentu == TECLA_DOWN)
	{
		if (ebentu == TECLA_SPACE && jokalaria.pos.y==425)
		{
			jokalaria.pos.y = jokalaria.pos.y - 12;
		}

		if (ebentu == TECLA_DOWN)
		{
			jokalaria.pos.y = jokalaria.pos.y + 12;
		}
		
	}

	if(jokalaria.pos.y<425)
	{
		while (jokalaria.pos.y > 300)
		{
			Sleep(6);
			pantailaGarbitu();
			jokalaria.pos.x = jokalaria.pos.x + 1;
			jokalaria.pos.y = jokalaria.pos.y - 2;
			irudiaMugitu(jokalaria.id, jokalaria.pos.x, jokalaria.pos.y);
			irudiakMarraztu();
			pantailaBerriztu();
		}
	}
	if (jokalaria.pos.y <= 300)
	{
		while (jokalaria.pos.y < 425)
		{
			Sleep(6);
			pantailaGarbitu();
			jokalaria.pos.y = jokalaria.pos.y + 2;
			jokalaria.pos.x = jokalaria.pos.x + 1;
			irudiaMugitu(jokalaria.id, jokalaria.pos.x, jokalaria.pos.y);
			irudiakMarraztu();
			pantailaBerriztu();
		}
	}
    egoera = JOKOA_egoera(jokalaria, obstakulua);
  } while (egoera == JOLASTEN);
  irudiaKendu(jokalaria.id);
  irudiaKendu(obstakulua.id);
  irudiaKendu(fondo.id);
  irudiaKendu(meta.id);
  toggleMusic();
  audioTerminate();
  pantailaGarbitu();
  pantailaBerriztu();
  return egoera;
}

EGOERA JOKOA_egoera(JOKO_ELEMENTUA jokalaria, JOKO_ELEMENTUA oztopoa) {
  EGOERA  ret = JOLASTEN;
  if (jokalaria.pos.x >oztopoa.pos.x - 20 && jokalaria.pos.x <oztopoa.pos.x + 20 && jokalaria.pos.y >oztopoa.pos.y - 20 && jokalaria.pos.y <oztopoa.pos.y + 20) {
    ret = IRABAZI;
  }
  else if (jokalaria.pos.x > 600) {
    ret = GALDU;
  }
  return ret;
}


int JOKOA_jokalariaIrudiaSortu() 
{
  int martzianoId = -1;
  martzianoId = irudiaKargatu(".\\img\\personaje.bmp");
  irudiaMugitu(martzianoId, 10, 239);
  pantailaGarbitu();
  irudiakMarraztu();
  pantailaBerriztu();
  return martzianoId;

}
int JOKOA_jokalariaIrudiaSortu2()
{
	int martzianoId = -1;
	martzianoId = irudiaKargatu(".\\img\\portada.bmp");
	irudiaMugitu(martzianoId, 0, 0);
	pantailaGarbitu();
	irudiakMarraztu();
	pantailaBerriztu();
	return martzianoId;

}
int JOKOA_jokalariaIrudiaSortu3()
{
	int martzianoId = -1;
	martzianoId = irudiaKargatu(".\\img\\play.bmp");
	irudiaMugitu(martzianoId, 300, 300);
	pantailaGarbitu();
	irudiakMarraztu();
	pantailaBerriztu();
	return martzianoId;

}
int JOKOA_jokalariaIrudiaSortu4()
{
	int martzianoId = -1;
	martzianoId = irudiaKargatu(".\\img\\fondo.bmp");
	irudiaMugitu(martzianoId, 10, 239);
	pantailaGarbitu();
	irudiakMarraztu();
	pantailaBerriztu();
	return martzianoId;

}
int JOKOA_jokalariaIrudiaSortu5()
{
	int martzianoId = -1;
	martzianoId = irudiaKargatu(".\\img\\meta.bmp");
	irudiaMugitu(martzianoId, 10, 239);
	pantailaGarbitu();
	irudiakMarraztu();
	pantailaBerriztu();
	return martzianoId;

}
int JOKOA_jokalariaIrudiaSortu1()
{
	int martzianoId = -1;
	martzianoId = irudiaKargatu(".\\img\\pintxo.bmp");
	irudiaMugitu(martzianoId, 10, 239);
	pantailaGarbitu();
	irudiakMarraztu();
	pantailaBerriztu();
	return martzianoId;

}

POSIZIOA ERREALITATE_FISIKOA_mugimendua(POSIZIOA posizioa) {
  posizioa.y = posizioa.y + 1;
  posizioa.x = posizioa.x + 1;
  return posizioa;
}

int  jokoAmaierakoa(EGOERA egoera)
{
  int ebentu = 0, id;
  int idAudioGame;

  loadTheMusic(BUKAERA_SOUND_1);
  if (egoera == IRABAZI) {
    idAudioGame = loadSound(JOKOA_SOUND_WIN);
    playSound(idAudioGame);
  }
  else {
    idAudioGame = loadSound(JOKOA_SOUND_LOOSE);
    playSound(idAudioGame);
  }
  id=BUKAERA_irudiaBistaratu();
  do 
  {
    ebentu = ebentuaJasoGertatuBada();
  } while ((ebentu!= TECLA_RETURN) && (ebentu!= SAGU_BOTOIA_ESKUMA));
  audioTerminate();
  irudiaKendu(id);
  return (ebentu != TECLA_RETURN) ? 1 : 0;
}

int BUKAERA_irudiaBistaratu() {
  int id = -1;
  id = irudiaKargatu(BUKAERA_IMAGE);
  irudiaMugitu(id, 200, 200);
  pantailaGarbitu();
  irudiakMarraztu();
  pantailaBerriztu();
  return id;
}

