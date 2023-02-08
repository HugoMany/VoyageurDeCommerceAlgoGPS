// TD4AlgoS4.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <cmath>
//#include <bits/stdc++.h>

	//Partie 1:

/*
a)
			Lille	New York	Stockholm	Bergen	Amsterdam	Londre	
Lille		0		5 830		1 356		1 095	232			243		
New York	5 830	0			6 340		5 630	5 880		5 590	
Stockholm	1 356	6 340		0			724		1 110		1 430	
Bergen		1 095	5 630		724			0		995			1 045	
Amsterdam	232		5 880		1 110		995		0			358		
Londre		243		5 590		1 430		1 045	358			0		

b)
Il y a 6! possibilité, 6x5x4x3x2=720



*/


// Definitions des CST
constexpr int codeASCIIde_a = 97;
constexpr int codeASCIIde_A = 65;
constexpr int nombreDeLettres = 26;
constexpr int tailleMinNomVille = 4;
constexpr int tailleMaxNomVille = 12;
constexpr int grainePourLeRand = 1;
constexpr int nombreDeVilles = 4;
constexpr int nombreCombinaisons = 24;
constexpr int tailleCoteCarte = 100;


const double earthRadiusKm = 6371.0;

using namespace std;
double cityVectToDistanceVect(vector<string>& villes);
void toutesLesPermutations(vector<string>& villes, int debut, int fin);

double deg2rad(double deg) {
	return (deg * 3.14 / 180);
}

double getDistanceFromLatLonInKm(double lat1, double lon1, double lat2, double lon2) {
	double dLat = deg2rad(lat2 - lat1);
	double dLon = deg2rad(lon2 - lon1);
	double a = sin(dLat / 2) * sin(dLat / 2) + cos(deg2rad(lat1)) * cos(deg2rad(lat2)) * sin(dLon / 2) * sin(dLon / 2);
	double c = 2 * atan2(sqrt(a), sqrt(1 - a));
	return earthRadiusKm * c;
}


vector<string> villes = { "Lille","New York","Stockholm","Bergen","Amsterdam","Londre" };
vector<pair<double, double>> co = { {50.6365654,3.0635282},{40.7127281,-74.0060152},{59.3251172,18.0710935},{60.3943055,5.3259192},{52.3727598,4.8936041},{51.5073219,-0.1276474} };
map<string, pair<double, double>	> cityCoord;
vector<pair<double, vector<string>>> allDist;

int main()
{
	//Mise en Map avec Coord
	
	int idx = 0;
	while (idx != villes.size())
	{
		cityCoord[villes[idx]] = co[idx];
		idx++;
	}
	toutesLesPermutations(villes, 0, villes.size() - 1);

	int bestIdx=0;
	double smallDistance = allDist[0].first;
	for (int i = 0; i < allDist.size()-1; i++)
	{
		if (smallDistance > allDist[i + 1].first) {
			bestIdx = i + 1;
			smallDistance = allDist[i + 1].first;
		}
	}
	
	cout << "La Distance la plus petite est :" << allDist[bestIdx].first<<" km" << endl;
	cout << "\nLa meilleur sequence pour faire ce trajet en terme de distance est:"<<endl;
	for (int i = 0; i < allDist[bestIdx].second.size(); i++)
	{
		cout << allDist[bestIdx].second[i]<<" -> ";
	}
		
	cout << endl;


	return 0;
}
/// <summary>
/// Surcharge d'operateur pour l'affiches d'un vector
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="monStylo"></param>
/// <param name="v"></param>
/// <returns></returns>
template <typename T>
ostream& operator<<(ostream& monStylo, const vector<T>& v)
{
	monStylo << "[";
	for (int i = 0; i < v.size(); ++i) {
		monStylo << v[i];
		if (i != v.size() - 1)
			monStylo << ", ";
	}
	monStylo << "]\n";
	return monStylo;
}
/// <summary>
/// Prend un vector de ville et calcul la distance total du trajet(trajet dans l'ordre du vector)
/// </summary>
/// <param name="villes"></param>
/// <returns>Distance total pour partcourir toutes les villes</returns>
double cityVectToDistanceVect(vector<string>& villes) {
	double totalDist=0;
	for (int i = 0; i < villes.size()-1; i++)
	{
		totalDist +=getDistanceFromLatLonInKm(cityCoord[villes[i]].first, cityCoord[villes[i]].second, cityCoord[villes[i+1]].first, cityCoord[villes[i+1]].second);
	}
	return totalDist;
}

/// <summary>
/// Donne toutes les permutations possibles de la sequence de villes données en vecteur: (n-1)!/2 Possibilité attention à l'explosion combinatoire.
/// </summary>
/// <param name="villes"></param>
/// <param name="debut"></param>
/// <param name="fin"></param>
void toutesLesPermutations(vector<string>& villes, int debut, int fin)
{
	if (debut == fin)
		allDist.push_back(make_pair(cityVectToDistanceVect(villes), villes));
	else
	{
		// Permutations made
		for (int i = debut; i <= fin; i++)
		{
			// echange des deux villes
			string temp = villes[debut];
			villes[debut] = villes[i];
			villes[i] = temp;

			// Appel Recursif
			toutesLesPermutations(villes, debut + 1, fin);
			// On revient à la situation précédente
			string temp2 = villes[debut];
			villes[debut] = villes[i];
			villes[i] = temp2;
		}
	}
	
}

