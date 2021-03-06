// ConsoleApplication5.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include <iostream>
#include "individu.h"
#include <fstream>
#include <sstream>
#include <limits>
#include <D:/boost/boost/archive/text_oarchive.hpp>
#include <D:/boost/boost/archive/text_iarchive.hpp>



#define TAILLE 5
//************************************************************************************************************* PROTOTYPES
void switchMenu(individu *personne[TAILLE], string fileName, string serialName);
void readFile(string fileName);
void createObject(individu *personne[TAILLE]);
void writeData(individu *personne[TAILLE], string fileName);
void searchFile(string fileName);
void serialFile(individu *personne[1000], string fileName);
void readSerialFile(string serialName);

//************************************************************************************************************* NAMESPACE
using namespace std;

//************************************************************************************************************* MAIN FUNCTION
int main(void)
{ 
	//VARIABLES
	individu *personne[TAILLE]; // création du tableau d'objet personne
	string fileName = "fichier.txt"; // nom statique du fichier de texte (brut)
	string serialName = "fichierDeSerialisation"; // nom statique du fichier de texte seriablié

	createObject(personne); // fonction de création des objets
	switchMenu(personne, fileName, serialName); // lancement du menu

	system("pause");
	return 0;
}

//************************************************************************************************************* MENU FUNCTION
void switchMenu(individu *personne[TAILLE], string fileName, string serialName)
{
	//VARIABLES
	int switchValue = 0; //variable de choix

	cout << "1. Ajout dans le fichier" << endl;
	cout << "2. Lecture du fichier" << endl;
	cout << "3. Rechercher dans le fichier" << endl;
	cout << "4. Créer un fichier serialise" << endl;
	cout << "5. Ouvrir un fichier serialise" << endl;

	cout << "\nEntrez un nombre\n";
	cin >> switchValue;
	//Code verifiant que la saisi est bien un nombre
	while (1)
	{
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Vous n avez pas saisi de nombre" << endl;
				cin >> switchValue;
		}
		if (!cin.fail())
			break;
	}
	// envoie vers les differentes fonction de l'application par rapport au choix de l'utilisateur
	switch(switchValue){
	case 1: writeData(personne, fileName); break;
	case 2: readFile(fileName); break;
	case 3: searchFile(fileName); break;
	case 4: serialFile(personne, serialName); break;
	case 5: readSerialFile(serialName); break;
	default: switchMenu(personne, fileName, serialName); break;
	}
}

//************************************************************************************************************* READ FILE CONTENT FUNCTION
void readFile(string fileName)
{
	//VARIABLES
	ifstream fichier; 
	fichier.open(fileName.c_str(), ios::in);   // ios::in pour la lecture
	string contenu; // contenu recevra les lignes a afficher


	if (fichier) // verification de la presence du fichier
	{
		while (getline(fichier, contenu, '\n'))//tant qu'on a des lignes, on les places dans contenu
		{
			cout << contenu << endl; // on affiche la ligne}
		}
	}
	else
		cerr << "Impossible d'ouvrir le fichier !" << endl;

	fichier.close();  // on ferme le fichier
	main();
}

//************************************************************************************************************* SEARCH IN READED FILE CONTENT FUNCTION
void searchFile(string fileName)
{
	//VARIABLES
	ifstream fichier;
	fichier.open(fileName.c_str(), ios::in);   // ios::in pour la lecture
	char charMot[1000]; //tableau statique pour la saisi de recherche
	string contenu;
	int value = 0; //curseur qui permet de comparer la longeur du mot cherché et celle du mot saisi

	cout << "Saisissez un Nom a chercher : ";
		cin >> charMot; // saisi utilisateur 
		int longMot = strlen(charMot); // calcul le nombre de caractere dans la recherche
	if (fichier)// verification de la presence du fichier
	{

			while(getline(fichier, contenu, '\n')) // tu recupere une ligne de ton fichier sous la forme d'un string 
			{
			
				for (int i = 0; i < contenu.length(); i++) //contenu[i] renverra le caractère placer a la i ème position. 
				{
					if (charMot[i] == contenu[i]) // on compare le Iieme caractere saisi au Iième caractere de la ligne
					{
						value++;
						if (value == longMot) // autre verification : si le mot saisi est <= en taille au mot cherché (et que les caractere sont identique) alors c'est OK
						{
							cout << contenu << endl;// on affiche la ligne
							cout << "\n";
							value = 0;
						}
					}

				}
		}
	}
	else
		cerr << "Impossible d'ouvrir le fichier !" << endl;


	fichier.close();  // on ferme le fichier
	main(); // retour au menu
}





//************************************************************************************************************* CREATE SOME OBJECT FOR THE SOFT TEST
void createObject(individu *personne[TAILLE])
{

	personne[0] = new individu("L01235", "JUNG", "Lucas", 12, 04, 1988, "Responsable");
	personne[1] = new individu("L01235", "RAMIREZ", "loic", 12, 04, 2000, "Technicien");
	personne[2] = new individu("L01235", "DUPONT", "adolphe", 12, 04, 1949, "Administratif");
	personne[3] = new individu("L01235", "JUNG", "Stephanie", 12, 04, 1976, "Technicien");
	personne[4] = new individu("L01235", "BRENSTEIN", "Lucie", 22, 04, 1996, "Technicien");

}

//************************************************************************************************************* WRITE CONTENT FUNCTION
void writeData(individu *personne[TAILLE], string fileName)
{
	//VARIABLES
	ofstream fichier;
	fichier.open(fileName.c_str(), ios::out);  // on ouvre le fichier en lecture

	if (fichier) // si le fichier existe
	{
		// on entre l'ensemble des information contenu dans les objets dans le fichier
		for (int i = 0; i < TAILLE; i++)
		{
			
			if (personne[i]->getBirthYear() != -1)
			{
				cout << "nom :" << personne[i]->getName() << endl;

				fichier << personne[i]->getName() << " " << personne[i]->getFirstName() << " ";
				fichier << personne[i]->getBirthday() << "/" << personne[i]->getBirthMounth() << "/" << personne[i]->getBirthYear() << " " << personne[i]->getJob() << endl;
			}
			else { cout << "vide" << endl; }

		}
	}


		
	fichier.close();  // on ferme le fichier
	main();

}

//************************************************************************************************************* SERIALIZE INTO FILE FUNCTION
void serialFile(individu *personne[1000], string serialName)
{
	//VARIABLES
	ofstream fichier;
	fichier.open(serialName.c_str(), ios::out);


	if (fichier)
	{
		{
			boost::archive::text_oarchive oa(fichier); // fonction de BOOST pour ouvrir le fichier en mode serialisation
			for (int i = 0; i < 5; i++)
			{

				if (personne[i]->getBirthYear() != -1)//verification que l'objet existe et qu'il est bien renseigné (d'office car objets créés a la main)
				{
					cout << "nom :" << personne[i]->getName() << endl; // affichage

					oa& personne[i];//insertion dans le fichier de serialisation
					
				}
			}
			cout << "Serialisation terminee" << endl; 

		}
	}
	else
		cerr << "Impossible d'ouvrir le fichier !" << endl;


	fichier.close();  // on ferme le fichier
	main();

}

//************************************************************************************************************* UNSERIALIZE TO OBJECTS FUNCTION
void readSerialFile(string serialName)
{
	//VARIABLES
	ifstream fichier;
	fichier.open(serialName.c_str(), ios::in);
	individu *serialPersonne[TAILLE]; // nouveau tableau d'objet de classe individu
	string contenu;

	serialPersonne[0] = new individu("", "", "", 12, 04, 1988, ""); // liste des objets vide (sauf les dates mais elle peuvent etre a 0)
	serialPersonne[1] = new individu("", "", "", 12, 04, 2000, "");
	serialPersonne[2] = new individu("", "", "", 12, 04, 1949, "");
	serialPersonne[3] = new individu("", "", "", 12, 04, 1976, "");
	serialPersonne[4] = new individu("", "", "", 22, 04, 1996, "");

	if (fichier)
	{

		boost::archive::text_iarchive ia(fichier); // ouverture du fichier pour la deserialisation

		for (int i = 0; i < TAILLE; i++) // on passe tout les objets
		{
			ia& serialPersonne[i]; // recuperation ligne par ligne et objet par objet
			cout << "verification de la reussite avec le nom : " << serialPersonne[i]->getName() << endl; // affichage de test

		}
		cout << "deserialisation terminee" << endl;
	}
	else
		cerr << "Impossible d'ouvrir le fichier !" << endl;

	fichier.close();  // on ferme le fichier
	main();

}



