#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#define PI 3.14
typedef struct tacka
{
	float x;
	float y;
}tiptacka;
typedef struct krug
{
	tiptacka centar;
	float polup;
}tipkrug;
typedef struct pravougaonik
{
	tiptacka gorelevo;
	tiptacka doledesno;
}tippravougaonik;

tiptacka unesitacku()
{
	tiptacka pomtacka;
	printf("Unesi x:\n");
	scanf(" %f", &pomtacka.x);
	printf("Unesi y:\n");
	scanf(" %f", &pomtacka.y);
	return pomtacka;
}
float udaljenosttacaka(tiptacka T1, tiptacka T2)
{
	return sqrtf(powf(T2.x - T1.x, 2) + powf(T2.y - T1.y, 2));
}
tipkrug unesikrug()
{
	tipkrug pomkrug;
	printf("Unesi centar kruga:\n");
	pomkrug.centar = unesitacku();
	printf("Unesi poluprecnik:\n");
	scanf("%f", &pomkrug.polup);
	return pomkrug;
}
float obimkruga(tipkrug kr)
{
	return 2 * kr.polup * PI;
}
void prikazkruga(tipkrug kr)
{
	printf("Krug: (%f,%f)-%f\n", kr.centar.x, kr.centar.y, kr.polup);
}
tippravougaonik unesipravougaonik()
{
	tippravougaonik pomprav;
	printf("Unesi tacku gore levo pravougaonika\n");
	pomprav.gorelevo = unesitacku();
	printf("Unesi tacku dole desno pravougaonika\n");
	pomprav.doledesno = unesitacku();
	return pomprav;
}
float povrsinapravougaonika(tippravougaonik pr)
{
	return (pr.doledesno.x - pr.gorelevo.x) * (pr.gorelevo.y - pr.doledesno.y);
}
// Fja za određivanje udaljenosti 
// tačke od centra kruga
float udaljTackeOdKruga(tiptacka t, tipkrug k)
{
	//return sqrt(pow(t.x - k.centar.x, 2) +
		//pow(t.y - k.centar.y, 2));
	return udaljenosttacaka(t, k.centar);
}
//Za određivanje udaljenosti tačke od pravougaonika 
// (najbližeg temena pravougaonika)
float udaljTackeOdPravougaonika
(tiptacka t, tippravougaonik p)
{
	float d1 = udaljenosttacaka(t, p.gorelevo);
	float d2 = udaljenosttacaka(t, p.doledesno);
	return d1 < d2 ? d1 : d2;
}
//Za određivanje udaljenosti dva kruga - najbližih tačaka 
float udaljenostDvaKruga(tipkrug k1, tipkrug k2)
{
	return udaljenosttacaka(k1.centar, k2.centar);
}
// Za određivanje da li je tačka unutar kruga
int tackaJeUnutarKruga(tiptacka t, tipkrug k)
{
	if (udaljenosttacaka(t, k.centar) < k.polup)
		return 1;//true
	else
		return 0;//false
}
int main()
{
	tiptacka T1, kpoc;
	tipkrug K1, K2;
	tippravougaonik P1;
	float D, obim, povrs;

	kpoc.x = 0;
	kpoc.y = 0;
	T1 = unesitacku();
	D = udaljenosttacaka(T1, kpoc);
	printf("D=%f\n", D);
	K1 = unesikrug();
	obim = obimkruga(K1);
	printf("O=%f\n", obim);
	D = udaljenosttacaka(K1.centar, kpoc);
	printf("D centra kruga od 0,0 = %f\n", D);
	D = udaljenosttacaka(T1, K1.centar);
	printf("D centra kruga od T1 = %f\n", D);
	P1 = unesipravougaonik();
	povrs = povrsinapravougaonika(P1);
	printf("P = %f\n", povrs);
	D = udaljenosttacaka(P1.gorelevo, P1.doledesno);
	printf("Dijagonala pravougaonika = %f\n", D);
	K2 = unesikrug();
	if (K1.polup > K2.polup && 
		udaljenosttacaka(K1.centar, K2.centar) < K1.polup)
	{
		K1.polup += K2.polup;
		K2.polup = 0;
	}
	if (K2.polup > K1.polup && 
		udaljenosttacaka(K1.centar, K2.centar) < K2.polup)
	{
		K2.polup += K1.polup;
		K1.polup = 0;
	}
	prikazkruga(K1);
	prikazkruga(K2);
	printf("Udaljenost K1-K2 je %.2f\n", udaljenostDvaKruga(K1, K2));
	if (tackaJeUnutarKruga(T1, K1))
		printf("T1 je unutar kruga K1\n");
	else
		printf("T1 je van kruga K1\n");
	return 0;
}